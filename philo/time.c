/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:03:10 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/18 11:10:01 by asemsey          ###   ########.fr       */
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

// pause for exactly ms msec
void	ft_msleep(long int ms, int *end_sim, pthread_mutex_t *die)
{
	long int	start;
	long int	remaining;

	ms *= 1000;
	start = ft_timeofday();
	while (ft_timeofday() - start < ms)
	{
		if (get_int(end_sim, die))
			return ;
		remaining = ms - (ft_timeofday() - start);
		if (remaining > 10000)
		{
			if (get_int(end_sim, die))
				return ;
			usleep(remaining / 100);
		}
		else
			while (ft_timeofday() - start < ms)
				;
	}
}

// pause for exactly ms msec
// void	ft_msleep(long int ms, int *end_sim, pthread_mutex_t *die)
// {
// 	ft_usleep(ms * 1000, end_sim, die);
// }
