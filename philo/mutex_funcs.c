/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 13:47:17 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/16 15:04:39 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_int(int *var, pthread_mutex_t *mutex)
{
	int	ret;

	pthread_mutex_lock(mutex);
	ret = *var;
	pthread_mutex_unlock(mutex);
	return (ret);
}

long int	get_long(long int *var, pthread_mutex_t *mutex)
{
	long int	ret;

	pthread_mutex_lock(mutex);
	ret = *var;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	set_int(int *var, int value, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	*var = value;
	pthread_mutex_unlock(mutex);
}

void	set_long(long int *var, long int value, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	*var = value;
	pthread_mutex_unlock(mutex);
}

void	increment_int(int *var, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	*var = *var + 1;
	pthread_mutex_unlock(mutex);
}
