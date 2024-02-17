/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:15:52 by asemsey           #+#    #+#             */
/*   Updated: 2024/02/17 14:44:12 by asemsey          ###   ########.fr       */
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
		if (now - phil->last_meal >= phil->data->life_time * 1000)
			break ;
		phil = phil->right;
	}
	ft_status(phil, 5);
}

void	*live(void *param)
{
	t_philo	*p;

	p = (t_philo *)param;
	p->last_meal = get_utimestamp(p->data->start);
	while (1)
	{
		thinking(p);
		eating(p);
		sleeping(p);
	}
	// exit(EXIT_SUCCESS);
	return (NULL);
}
