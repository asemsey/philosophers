/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_fork.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:23:39 by asemsey           #+#    #+#             */
/*   Updated: 2024/02/14 10:39:39 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		f = new_fork((*phil)->name);
		(*phil)->r_fork = f;
		*phil = (*phil)->right;
		(*phil)->l_fork = f;
		if (*phil == p)
			break ;
	}
	*phil = p;
}

// add all forks to the table 2
void	all_forks(t_philo **phil)
{
	int	len;

	if (!phil || !*phil)
		return ;
	len = (highest(*phil))->name;
	while (len > 0)
		add_fork(phil, new_fork(len--));
}

// add the new fork to the correct philosophers
void	add_fork(t_philo **phil, t_fork *new)
{
	t_philo	*p;

	if (!new || !phil || !*phil)
		return ;
	p = *phil;
	while (*phil)
	{
		if ((*phil)->name == new->name)
		{
			(*phil)->r_fork = new;
			*phil = (*phil)->right;
			(*phil)->l_fork = new;
			break ;
		}
		*phil = (*phil)->right;
		if (*phil == p)
			break ;
	}
	*phil = p;
}

// create a fork with the given name
t_fork	*new_fork(int name)
{
	t_fork	*fork;

	fork = malloc(sizeof(t_fork));
	if (!fork)
		return (NULL);
	fork->name = name;
	fork->locked = 0;
	return (fork);
}
