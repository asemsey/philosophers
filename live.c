/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 15:09:52 by asemsey           #+#    #+#             */
/*   Updated: 2024/02/04 12:50:06 by asemsey          ###   ########.fr       */
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

	start = get_timestamp(phil->data->start);
	printf("%ld %d is sleeping\n", start, phil->name);
	phil->state = 0;
	// 	usleep(1000 * phil->data->sleep_time);
	while (get_timestamp(phil->data->start) - phil->last_meal <= phil->data->life_time)
	{
		if (get_timestamp(phil->data->start) - start >= phil->data->sleep_time)
			return (1);
		usleep(990);//?
	}
	return (0);
}

void	eating(t_philo *phil)
{
	printf("%ld %d is eating\n", get_timestamp(phil->data->start), phil->name);
	phil->state = 1;
	usleep(1000 * phil->data->eat_time);
	pthread_mutex_unlock(&(phil->l_fork->mutex));
	phil->l_fork->locked = 0;
	pthread_mutex_unlock(&(phil->r_fork->mutex));
	phil->r_fork->locked = 0;
	if (phil->data->min_meals && phil->meals >= phil->data->min_meals)
	{
		usleep(100);//?
		printf("%ld %d has eaten %d meals\n", get_timestamp(phil->data->start), phil->name, phil->meals);
		usleep(100);//?
		exit(EXIT_SUCCESS);
	}
	phil->meals++;
	phil->last_meal = get_timestamp(phil->data->start);
}

int	thinking(t_philo *phil)
{
	printf("%ld %d is thinking\n", get_timestamp(phil->data->start), phil->name);
	phil->state = 2;
	while (get_timestamp(phil->data->start) - phil->last_meal <= phil->data->life_time)
	{
		if (!phil->l_fork->locked)
		{
			pthread_mutex_lock(&(phil->l_fork->mutex));
			printf("%ld %d has taken a fork\n", get_timestamp(phil->data->start), phil->name);
			phil->l_fork->locked = phil->name;
		}
		if (!phil->r_fork->locked)
		{
			pthread_mutex_lock(&(phil->r_fork->mutex));
			printf("%ld %d has taken a fork\n", get_timestamp(phil->data->start), phil->name);
			phil->r_fork->locked = phil->name;
		}
		if (phil->l_fork->locked == phil->name && phil->r_fork->locked == phil->name)
			return (1);
		usleep(5);//?
	}
	return (0);
}

// get the difference between start and now in ms
long int	get_timestamp(long int start)
{
	struct timeval	time;
	long int		now;

	now = 0;
	if (gettimeofday(&time, NULL) == 0)
	{
		now = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	}
	return (now - start);
}

// get the current time in ms
long int	get_start()
{
	struct timeval	time;
	long int		now;

	now = 0;
	if (gettimeofday(&time, NULL) == 0)
	{
		now = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	}
	return (now);
}
