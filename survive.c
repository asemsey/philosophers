/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   survive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 15:09:52 by asemsey           #+#    #+#             */
/*   Updated: 2024/02/18 14:45:50 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo *phil)
{
	ft_status(phil, 0);
	ft_msleep(phil->data->sleep_time);
}

void	eating(t_philo *phil)
{
	set_int(&phil->is_eating, 1, &phil->data->m_var);
	// phil->is_eating = 1;
	ft_status(phil, 3);
	ft_msleep(phil->data->eat_time);
	set_int(&phil->l_fork->locked, 0, &phil->data->m_var);
	// phil->l_fork->locked = 0;
	set_int(&phil->r_fork->locked, 0, &phil->data->m_var);
	// phil->r_fork->locked = 0;
	pthread_mutex_unlock(&(phil->l_fork->mutex));
	pthread_mutex_unlock(&(phil->r_fork->mutex));
	// phil->last_meal = get_utimestamp(phil->data->start);
	set_long(&phil->last_meal, get_utimestamp(phil->data->start), &phil->data->m_var);
	if (phil->data->min_meals && phil->meals >= phil->data->min_meals)
		ft_status(phil, 4);
	phil->meals++;
	set_int(&phil->is_eating, 0, &phil->data->m_var);
	// phil->is_eating = 0;
}

void	thinking(t_philo *phil)
{
	ft_status(phil, 1);
	// while (get_int(&phil->left->is_eating, &phil->data->m_var))
	// 	ft_msleep(1);
	while (1)
	{
		if (!get_int(&phil->l_fork->locked, &phil->data->m_var)
			&& !get_int(&phil->r_fork->locked, &phil->data->m_var))
		{
			pthread_mutex_lock(&(phil->l_fork->mutex));
			pthread_mutex_lock(&(phil->r_fork->mutex));
			set_int(&phil->l_fork->locked, phil->name, &phil->data->m_var);
			// phil->l_fork->locked = phil->name;
			set_int(&phil->r_fork->locked, phil->name, &phil->data->m_var);
			// phil->r_fork->locked = phil->name;
			ft_status(phil, 2);
			return ;
		}
		usleep(5);
	}
}

void	ft_status(t_philo *phil, int state)
{
	long int	start;

	pthread_mutex_lock(&(phil->data->m_print));
	start = phil->data->start / 1000;
	if (state == 0)
		printf("%ld %d is sleeping\n", get_timestamp(start), phil->name);
	else if (state == 1)
		printf("%ld %d is thinking\n", get_timestamp(start), phil->name);
	else if (state == 2)
	{
		printf("%ld %d has taken a fork\n", get_timestamp(start), phil->name);
		printf("%ld %d has taken a fork\n", get_timestamp(start), phil->name);
	}
	else if (state == 3)
		printf("%ld %d is eating\n", get_timestamp(start), phil->name);
	else if (state == 4)
	{
		printf("%ld %d has eaten %d meals\n", get_timestamp(start), phil->name, phil->data->min_meals);
		exit(EXIT_SUCCESS);
	}
	pthread_mutex_unlock(&(phil->data->m_print));
}
