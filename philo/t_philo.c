/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:35:16 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/18 11:07:10 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*new_philo(int name, t_data *data);
void	add_to_table(t_philo **phil, t_philo *new);

// create the linked list of philosophers
t_philo	*create_table(int count, t_data *data)
{
	t_philo	*p;
	int		i;

	i = 1;
	p = NULL;
	while (i <= count)
		add_to_table(&p, new_philo(i++, data));
	if (i > 1)
		p->left = highest(p);
	create_forks(&p);
	return (p);
}

// add a philosopher with the next number
void	add_to_table(t_philo **phil, t_philo *new)
{
	t_philo	*p;

	if (!new)
		return ;
	if (!*phil)
	{
		*phil = new;
		(*phil)->right = *phil;
		return ;
	}
	p = *phil;
	p = highest(p);
	p->right = new;
	new->left = p;
	new->right = *phil;
}

// create a philosopher with the given name
t_philo	*new_philo(int name, t_data *data)
{
	t_philo	*p;

	p = malloc(sizeof(t_philo));
	if (!p)
		return (NULL);
	p->name = name;
	p->left = NULL;
	p->right = NULL;
	p->data = data;
	p->is_eating = 0;
	p->t_since_think = 0;
	p->meals = 0;
	return (p);
}

// return the philosopher with the highest number
t_philo	*highest(t_philo *phil)
{
	while (phil && phil->right)
	{
		if (phil->right->name <= phil->name)
			break ;
		phil = phil->right;
	}
	return (phil);
}
