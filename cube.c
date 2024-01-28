/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 10:31:35 by asemsey           #+#    #+#             */
/*   Updated: 2024/01/28 11:39:30 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

typedef struct s_cube
{
	int	edge;
	int	volume;
	int	surface;
}	t_cube;

void	*get_v(void *arg)
{
	t_cube	*cube = (t_cube *)arg;
	cube->volume = cube->edge * cube->edge * cube->edge;
	printf("done (v)\n");
	return (cube);
}

void	*get_s(void *arg)
{
	t_cube	*cube = (t_cube *)arg;
	cube->surface = cube->edge * cube->edge * 6;
	printf("done (s)\n");
	return (cube);
}

int main(int argc, char const *argv[])
{
	pthread_t	a = NULL;
	pthread_t	b = NULL;
	t_cube		c;

	(void)argc;
	(void)argv;
	c.edge = 5;
	printf("edge: %d\n", c.edge);
	pthread_create(&a, NULL, get_s, (void *)&c);
	pthread_create(&b, NULL, get_v, (void *)&c);
	pthread_join(a, NULL);
	pthread_join(b, NULL);
	printf("volume: %d\nsurface: %d\n", c.volume, c.surface);
	return (0);
}
