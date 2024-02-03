/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 15:09:52 by asemsey           #+#    #+#             */
/*   Updated: 2024/02/03 10:49:46 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *phil);
int		sleeping(t_philo *phil);
int		thinking(t_philo *phil);

/*
if (startcondition)
	eating()
	the loop:
		if (!sleeping())
			die;
		if (!thinking())
			die;
		eating()
		repeat...
*/

void	*live(void *param)
{
	t_philo	*p;

	p = (t_philo *)param;
	p->last_meal = get_timestamp(p->data->start);
	if (p->name % 2)
		eating(p);
	while (1)
	{
		if (!sleeping(p))
			break ;
		if (!thinking(p))
			break ;
		eating(p);
	}
	printf("philosopher %d has died :(\n", p->name);
	exit(EXIT_SUCCESS);// death
	return (NULL);
}

int	sleeping(t_philo *phil)
{
	long int	start;

	start = get_timestamp(phil->data->start);
	printf("%ld   %d is sleeping\n", start, phil->name);
	phil->state = 0;
	// sleep for data->sleep_time ms while checking if still alive
	// that`s:	usleep(1000 * phil->data->sleep_time);
	while (get_timestamp(phil->data->start) - phil->last_meal <= phil->data->life_time)
	{
		if (get_timestamp(phil->data->start) - start >= phil->data->sleep_time)
			return (1);
		usleep(995);//???
	}
	// death:
	return (0);
}

void	eating(t_philo *phil)
{
	printf("%ld   %d is eating\n", get_timestamp(phil->data->start), phil->name);
	phil->state = 1;
	// take two forks (mutex)
	usleep(1000 * phil->data->eat_time);
	// return the forks
	if (phil->data->min_meals && phil->meals >= phil->data->min_meals)
	{
		printf("%ld   %d has eaten %d meals\n", get_timestamp(phil->data->start), phil->name, phil->meals);
		exit(EXIT_SUCCESS);
	}
	phil->last_meal = get_timestamp(phil->data->start);
}

int	thinking(t_philo *phil)
{
	printf("%ld   %d is thinking\n", get_timestamp(phil->data->start), phil->name);
	phil->state = 2;
	while (get_timestamp(phil->data->start) - phil->last_meal <= phil->data->life_time)
	{
		// 		keep checking if the forks are available
		// if (forks_available)
		// {
		// 	return (1);
		// 	// eat next!!!
		// }
		usleep(5);//????
	}
	// death:
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
