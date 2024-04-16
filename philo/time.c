/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:03:10 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/16 15:04:23 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// current time in usec / start time
long int	ft_timeofday(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == 0)
		return ((time.tv_sec * 1000000) + (time.tv_usec));
	return (-1);
}

// get the difference between start and now in msec
long int	get_timestamp(long int mstart)
{
	long int		now;

	now = ft_timeofday();
	if (now >= 0)
		return ((now / 1000) - mstart);
	return (-1);
}

// get the difference between start and now in usec
long int	get_utimestamp(long int ustart)
{
	long int		now;

	now = ft_timeofday();
	if (now >= 0)
		return (now - ustart);
	return (-1);
}

// pause for exactly us usec
void	ft_usleep(long int us, int *end_sim, pthread_mutex_t *die)
{
	long int	start;
	long int	remaining;

	start = ft_timeofday();
	while (ft_timeofday() - start < us)
	{
		if (get_int(end_sim, die))
			return ;
		remaining = us - (ft_timeofday() - start);
		if (remaining > 10000)
		{
			if (get_int(end_sim, die))
				return ;
			usleep(remaining / 10);
		}
		else
			while (ft_timeofday() - start < us)
				;
	}
}

// pause for exactly ms msec
void	ft_msleep(long int ms, int *end_sim, pthread_mutex_t *die)
{
	ft_usleep(ms * 1000, end_sim, die);
}
