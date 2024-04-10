/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:15:52 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/10 13:13:53 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*is_dead(void *param)
{
	t_philo		*phil;
	t_philo		*head;
	long int	now;

	phil = (t_philo *)param;
	head = phil;
	now = get_utimestamp(phil->data->start);
	while (phil)
	{
		if (phil == head)
			now = get_utimestamp(phil->data->start);
		if (now - get_long(&phil->last_meal, &phil->data->m_var) >= \
			phil->data->life_time * 1000 && !get_int(&phil->is_eating, \
			&phil->data->m_var))
			break ;
		phil = phil->right;
	}
	pthread_mutex_lock(&(phil->data->m_print));
	printf("%ld %d died\n", get_timestamp(phil->data->start / 1000), \
		phil->name);
	return (NULL);
}

int	get_think_counter(int name, int n)
{
	if (name == 1 || name == 2)
		return (0);
	if (name % 2 == 0)
		return ((n / 2) - ((name - 2) / 2));
	return ((n / 2) - ((name - 1) / 2));
}

// here!!!
void	live_odd(t_philo *phil, int n)
{
	int	loop;

	loop = 1;
	phil->t_since_think = get_think_counter(phil->name, n);
	if (phil->name == 2)
		thinking(phil, 2 * phil->data->eat_time);
	else if (phil->name % 2 == 0 || phil->name == 1)
		thinking(phil, phil->data->eat_time);
	while (1)
	{
		if (phil->t_since_think == n / 2)
		{
			thinking(phil, phil->data->eat_time);
			phil->t_since_think = 0;
		}
		else if ((loop == 1 && !(phil->name == 1 || phil->name % 2 == 0))
			|| loop == 0)
			thinking(phil, 0);
		eating(phil);
		sleeping(phil);
		loop = 0;
	}
}

void	live_even(t_philo *phil)
{
	int	loop;

	loop = 1;
	if (phil->name % 2 == 0)
		thinking(phil, phil->data->eat_time);
	while (1)
	{
		if (loop != 1 || phil->name % 2 != 0)
			thinking(phil, 0);
		eating(phil);
		sleeping(phil);
		loop++;
	}
}

void	*live(void *param)
{
	t_philo	*p;
	int		n;

	p = (t_philo *)param;
	while (!get_int(&p->data->all_ready, &p->data->m_var))
		;
	set_long(&p->last_meal, get_utimestamp(p->data->start), &p->data->m_var);
	n = highest(p)->name;
	if (n == 1)
		p->l_fork->locked = 2;
	if (n % 2 == 0)
		live_even(p);
	else
		live_odd(p, n);
	return (NULL);
}
