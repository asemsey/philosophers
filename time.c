/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:03:10 by asemsey           #+#    #+#             */
/*   Updated: 2024/02/17 13:33:08 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// current time in usec / start time
long int	ft_timeofday(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == 0)
		return((time.tv_sec * 1000000) + (time.tv_usec));
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
void	ft_usleep(long int us)
{
	long int		start;

	start = ft_timeofday();
	while (ft_timeofday() - start <= (us - 10))
		usleep(10);
}

// pause for exactly ms msec
void	ft_msleep(long int ms)
{
	long int		start;

	start = ft_timeofday();
	while (ft_timeofday() - start <= (ms * 1000 - 20))
		usleep(20);
}
