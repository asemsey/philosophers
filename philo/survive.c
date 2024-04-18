/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   survive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 15:09:52 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/18 11:10:38 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_status(t_philo *phil, int state);

void	sleeping(t_philo *phil)
{
	if (get_int(&phil->data->end_sim, &phil->data->m_die))
		return ;
	ft_status(phil, 0);
	ft_msleep(phil->data->sleep_time, &phil->data->end_sim, &phil->data->m_die);
	phil->t_since_think++;
}

void	eating(t_philo *phil)
{
	if (get_int(&phil->data->end_sim, &phil->data->m_die))
		return ;
	set_int(&phil->is_eating, 1, &phil->data->m_var);
	set_long(&phil->last_meal, get_utimestamp(phil->data->start), \
		&phil->data->m_var);
	ft_status(phil, 3);
	ft_msleep(phil->data->eat_time, &phil->data->end_sim, &phil->data->m_die);
	pthread_mutex_lock(&(phil->l_fork->m_fork));
	pthread_mutex_lock(&(phil->r_fork->m_fork));
	phil->l_fork->locked = 0;
	phil->r_fork->locked = 0;
	pthread_mutex_unlock(&(phil->l_fork->m_fork));
	pthread_mutex_unlock(&(phil->r_fork->m_fork));
	increment_int(&phil->meals, &phil->data->m_var);
	set_int(&phil->is_eating, 0, &phil->data->m_var);
}

void	thinking(t_philo *phil, int ms)
{
	if (get_int(&phil->data->end_sim, &phil->data->m_die))
		return ;
	ft_status(phil, 1);
	if (ms > 0)
		ft_msleep(ms, &phil->data->end_sim, &phil->data->m_die);
	while (1)
	{
		if (get_int(&phil->data->end_sim, &phil->data->m_die))
			return ;
		pthread_mutex_lock(&(phil->l_fork->m_fork));
		pthread_mutex_lock(&(phil->r_fork->m_fork));
		if (!phil->l_fork->locked && !phil->r_fork->locked)
		{
			phil->l_fork->locked = phil->name;
			phil->r_fork->locked = phil->name;
			pthread_mutex_unlock(&(phil->l_fork->m_fork));
			pthread_mutex_unlock(&(phil->r_fork->m_fork));
			ft_status(phil, 2);
			return ;
		}
		pthread_mutex_unlock(&(phil->l_fork->m_fork));
		pthread_mutex_unlock(&(phil->r_fork->m_fork));
	}
}

void	ft_status(t_philo *phil, int state)
{
	long int	start;

	if (get_int(&phil->data->end_sim, &phil->data->m_die))
		return ;
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
	pthread_mutex_unlock(&(phil->data->m_print));
}
