/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 15:09:52 by asemsey           #+#    #+#             */
/*   Updated: 2024/02/14 13:33:08 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *phil);
int		sleeping(t_philo *phil);
int		thinking(t_philo *phil);

void	*live(void *param)
{
	t_philo	*p;

	p = (t_philo *)param;
	p->last_meal = get_timestamp(p->data->start);
	while (1)
	{
		if (!thinking(p))
			break ;
		eating(p);
		if (!sleeping(p))
			break ;
	}
	printf("%ld %d died\n", get_timestamp(p->data->start), p->name);
	destroy_mutexes(&p);
	exit(EXIT_SUCCESS);
	return (NULL);
}

int	sleeping(t_philo *phil)
{
	long int	start;

	// phil->state = 0;
	start = get_timestamp(phil->data->start);
	ft_status(phil, 0);
	while (get_timestamp(phil->data->start) - phil->last_meal <= phil->data->life_time)
	{
		if (get_timestamp(phil->data->start) - start >= phil->data->sleep_time)
			return (1);
		ft_usleep(1);//?
	}
	return (0);
}

void	eating(t_philo *phil)
{
	// phil->state = 1;
	ft_status(phil, 3);
	ft_usleep(phil->data->eat_time);
	pthread_mutex_unlock(&(phil->l_fork->mutex));
	phil->l_fork->locked = 0;
	pthread_mutex_unlock(&(phil->r_fork->mutex));
	phil->r_fork->locked = 0;
	if (phil->data->min_meals && phil->meals >= phil->data->min_meals)
	{
		ft_status(phil, 4);
		exit(EXIT_SUCCESS);
	}
	phil->meals++;
	phil->last_meal = get_timestamp(phil->data->start);
}

int	thinking(t_philo *phil)
{
	// phil->state = 2;
	ft_status(phil, 1);
	while (get_timestamp(phil->data->start) - phil->last_meal <= phil->data->life_time)
	{
		if (!phil->l_fork->locked)
		{
			pthread_mutex_lock(&(phil->l_fork->mutex));
			ft_status(phil, 2);
			phil->l_fork->locked = phil->name;
		}
		if (!phil->r_fork->locked)
		{
			pthread_mutex_lock(&(phil->r_fork->mutex));
			ft_status(phil, 2);
			phil->r_fork->locked = phil->name;
		}
		if (phil->l_fork->locked == phil->name && phil->r_fork->locked == phil->name)
			return (1);
		usleep(5);//?
	}
	return (0);
}

void	ft_status(t_philo *phil, int state)
{
	pthread_mutex_lock(&(phil->data->m_print));
	if (state == 0)
		printf("%ld %d is sleeping\n", get_timestamp(phil->data->start), phil->name);
	else if (state == 1)
		printf("%ld %d is thinking\n", get_timestamp(phil->data->start), phil->name);
	else if (state == 2)
		printf("%ld %d has taken a fork\n", get_timestamp(phil->data->start), phil->name);
	else if (state == 3)
		printf("%ld %d is eating\n", get_timestamp(phil->data->start), phil->name);
	else if (state == 4)
	{
		printf("%ld %d has eaten %d meals\n", get_timestamp(phil->data->start), phil->name, phil->data->min_meals);
		exit(EXIT_SUCCESS);
	}
	pthread_mutex_unlock(&(phil->data->m_print));
}
