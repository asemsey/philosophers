/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:15:52 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/18 11:00:22 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// if min_meals is set, checks if everyone has eaten min_meals
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

// check if any philosophers have died, returns their index or 0
int	is_dead(t_philo *phil, long int now)
{
	t_philo	*head;
	int		dead;

	head = phil;
	dead = 0;
	while (phil)
	{
		pthread_mutex_lock(&phil->data->m_var);
		if (now - phil->last_meal >= phil->data->life_time * 1000
			&& !phil->is_eating)
			dead = phil->name;
		pthread_mutex_unlock(&phil->data->m_var);
		phil = phil->right;
		if (phil == head || dead)
			break ;
	}
	return (dead);
}

void	monitor_status(t_philo *phil)
{
	int			dead;
	long int	now;

	dead = 0;
	while (1)
	{
		now = get_utimestamp(phil->data->start);
		dead = is_dead(phil, now);
		if (dead || (phil->data->min_meals
				&& all_ate_enough(phil, phil->data->min_meals)))
			break ;
		usleep(100);
	}
	set_int(&phil->data->end_sim, 1, &phil->data->m_die);
	if (dead)
	{
		pthread_mutex_lock(&(phil->data->m_print));
		printf("%ld %d died\n", get_timestamp(phil->data->start / 1000), dead);
		pthread_mutex_unlock(&(phil->data->m_print));
	}
}
