/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:03:10 by asemsey           #+#    #+#             */
/*   Updated: 2024/02/14 13:11:22 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	ft_timeofday(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == 0)
		return((time.tv_sec * 1000000) + (time.tv_usec));
	return (-1);
}

// get the difference between start and now in ms
long int	get_timestamp(long int start)
{
	long int		now;

	now = ft_timeofday();
	if (now >= 0)
		return ((now / 1000) - start);
	return (-1);
}

// get the current time in ms
// long int	get_start()
// {
// 	struct timeval	time;
// 	long int		now;

// 	now = 0;
// 	if (gettimeofday(&time, NULL) == 0)
// 		now = (time.tv_sec * 1000) + (time.tv_usec / 1000);
// 	return (now);
// }

void	ft_usleep(long int ms)
{
	long int		start;

	start = ft_timeofday();
	while (ft_timeofday() - start <= (ms * 1000 - 20))
		usleep(20);
}
