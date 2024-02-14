/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:35:16 by asemsey           #+#    #+#             */
/*   Updated: 2024/02/14 11:00:03 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	// all_forks(&p);
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
	p->state = 0;
	p->meals = 0;
	p->id = NULL;
	return (p);
}

// return the number of philosophers at the table
int	tablesize(t_philo *phil)
{
	int		size;
	t_philo	*start;

	size = 0;
	start = phil;
	while (phil)
	{
		size++;
		phil = phil->right;
		if (phil == start)
			break;
	}
	return (size);
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

// print info on all philosophers, with forks
void	print_table(t_philo *phil)
{
	if (!phil)
		return ;
	printf("left  name  right || l_fork  r_fork || eaten  min meals\n");
	printf("--------------------------------------------------\n");
	while (phil)
	{
		printf("%d     %d     %d     || %d      %d || %d   %d\n", phil->left->name,\
			phil->name, phil->right->name, phil->l_fork->name, phil->r_fork->name, phil->meals, phil->data->min_meals);
		if (phil == highest(phil))
			break ;
		phil = phil->right;
	}
	printf("--------------------------------------------------\n");
}

// free_all for circular list, with t_data and t_fork
void	free_philo(t_philo **phil)
{
	t_philo	*tmp;

	if (!phil || !*phil)
		return ;
	free((*phil)->data);
	while (*phil)
	{
		tmp = *phil;
		*phil = (*phil)->right;
		free(tmp->l_fork);
		free(tmp);
	}
}
