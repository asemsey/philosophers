/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:15:52 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/18 10:55:09 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	live_odd(t_philo *phil, int n)
{
	int	loop;

	loop = 1;
	if (phil->name == 2)
		thinking(phil, 2 * phil->data->eat_time);
	else if (phil->name % 2 == 0 || phil->name == 1)
		thinking(phil, phil->data->eat_time);
	while (1)
	{
		if (get_int(&phil->data->end_sim, &phil->data->m_die))
			return ;
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
		if (get_int(&phil->data->end_sim, &phil->data->m_die))
			return ;
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
	{
		if (p->name == 1 || p->name == 2)
			p->t_since_think = 0;
		else if (p->name % 2 == 0)
			p->t_since_think = (n / 2) - ((p->name - 2) / 2);
		else
			p->t_since_think = (n / 2) - ((p->name - 1) / 2);
		live_odd(p, n);
	}
	return (NULL);
}
