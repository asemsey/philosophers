/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:15:52 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/10 16:27:26 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_ate_enough(t_philo *phil, int min)
{
	t_philo	*head;

	head = phil;
	while (phil)
	{
		if (get_int(&phil->meals, &phil->data->m_var) < min)
			return (0);
		phil = phil->right;
		if (phil == head)
			break ;
	}
	return (1);
}

int	is_dead(t_philo *phil, long int now)
{
	if (now - get_long(&phil->last_meal, &phil->data->m_var) >= \
		phil->data->life_time * 1000 && !get_int(&phil->is_eating, \
		&phil->data->m_var))
		return (phil->name);
	return (0);
}

void	*monitor_status(void *param)
{
	t_philo		*phil;
	int			dead;
	long int	now;

	phil = (t_philo *)param;
	dead = 0;
	while (phil)
	{
		if (phil->name == 1)
			now = get_utimestamp(phil->data->start);
		if (phil->name == 1 && phil->data->min_meals && all_ate_enough(phil, \
			phil->data->min_meals))
			break ;
		dead = is_dead(phil, now);
		if (dead)
			break ;
		phil = phil->right;
	}
	pthread_mutex_lock(&(phil->data->m_print));
	if (dead)
		printf("%ld %d died\n", get_timestamp(phil->data->start / 1000), dead);
	return (NULL);
}
