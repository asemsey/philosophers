/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_fork.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:23:39 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/16 12:16:12 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// create a fork with the given name
t_fork	*new_fork(void)
{
	t_fork	*fork;

	fork = malloc(sizeof(t_fork));
	if (!fork)
		return (NULL);
	pthread_mutex_init(&(fork->m_fork), NULL);
	// fork->name = name;
	fork->locked = 0;
	return (fork);
}

// add all forks to the table
void	create_forks(t_philo **phil)
{
	t_philo	*p;
	t_fork	*f;

	if (!phil || !*phil)
		return ;
	p = *phil;
	while (*phil)
	{
		f = new_fork();
		(*phil)->r_fork = f;
		*phil = (*phil)->right;
		(*phil)->l_fork = f;
		if (*phil == p)
			break ;
	}
	*phil = p;
}
