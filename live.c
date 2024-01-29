/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 15:09:52 by asemsey           #+#    #+#             */
/*   Updated: 2024/01/29 17:32:56 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *phil);
void	sleep(t_philo *phil);
void	think(t_philo *phil);

void	*live(void *param)
{
	t_philo	*p;

	p = (t_philo *)param;

	if (p->name == 2)
		usleep(1000 * 1000 * 2);
	else
		usleep(1000 * 1000 * 4);
	printf("philosopher %d has died :(\n", p->name);
	exit(EXIT_SUCCESS);// death
	return (NULL);
}

// HERE!
void	eat(t_philo *phil)
{
	printf("%d %d is eating", );
	// change state
	// take two forks (mutex)
	// sleep data->eat_time ms
	// return the forks
}

void	sleep(t_philo *phil)
{
	// change state
	// sleep for data->sleep_time ms while checking if still alive
}

void	think(t_philo *phil)
{
	// change state
	// keep checking if the forks are available while checking if still alive
	// if yes, eat
}
