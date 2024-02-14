/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 10:26:38 by asemsey           #+#    #+#             */
/*   Updated: 2024/02/14 13:07:26 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *str, t_philo **phil)
{
	int	i;

	i = 0;
	if (phil)
		free_all((void **)phil);
	if (str)
		printf("Error\n%s\n", str);
	return (EXIT_FAILURE);
}

// create, detach / join threads
void	start_threads(t_philo **phil)
{
	t_philo	*head;

	head = *phil;
	(*phil)->data->start = ft_timeofday() / 1000;
	while (*phil)
	{
		pthread_create(&(*phil)->id, NULL, live, (void *)*phil);
		pthread_detach((*phil)->id);
		if ((*phil)->right == head)
			break ;
		*phil = (*phil)->right;
	}
	*phil = head;
	while (1)
		usleep(1000 * 10);
	destroy_mutexes(phil);
	free_philo(phil);
}

void leak(void)
{
	system("leaks philo");
}

// 1:[number_of_philosophers]  2:[time_to_die]  3:[time_to_eat]  4:[time_to_sleep]
// optional: 5:[number_of_times_each_philosopher_must_eat]
int main(int argc, char **argv)
{
	t_philo		*phil;

	// atexit(leak);
	if (check_args(argc, argv) == 0)
		return (ft_error("invalid arguments", NULL));
	phil = create_table(ft_atoi(argv[1]), get_data(argc, argv));
	if (!phil)
		return (EXIT_FAILURE);
	print_table(phil);
	start_threads(&phil);
	return (0);
}
