/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:15:52 by asemsey           #+#    #+#             */
/*   Updated: 2024/02/18 14:40:06 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*is_dead(void *param)
{
	t_philo	*phil;
	t_philo	*head;
	long int now;

	phil = (t_philo *)param;
	head = phil;
	now = get_utimestamp(phil->data->start);
	while (phil)
	{
		if (phil == head)
			now = get_utimestamp(phil->data->start);
		if (now - get_long(&phil->last_meal, &phil->data->m_var) >= \
			phil->data->life_time * 1000 && !phil->is_eating)
			break ;
		phil = phil->right;
	}
	pthread_mutex_lock(&(phil->data->m_print));
	printf("%ld %d died\n", get_timestamp(phil->data->start / 1000), phil->name);
	// print_table(highest(phil)->right);
	return (NULL);
}

void	live_odd(t_philo *phil)
{
	if (phil->name == 1)
		ft_msleep(phil->data->eat_time);
	if (phil->name == 1 || phil->name % 2 == 0)
		ft_msleep(phil->data->eat_time);
	while (1)
	{
		thinking(phil);
		eating(phil);
		sleeping(phil);
	}
}

void	live_even(t_philo *phil)
{
	if (phil->name % 2 == 0)
		ft_msleep(phil->data->eat_time);
	while (1)
	{
		thinking(phil);
		eating(phil);
		sleeping(phil);
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
		live_odd(p);
	return (NULL);
}
