/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 10:26:38 by asemsey           #+#    #+#             */
/*   Updated: 2024/02/17 16:40:40 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *str, t_philo **phil)
{
	int	i;

	i = 0;
	if (phil)
		free_philo(phil);
	if (str)
		printf("Error\n%s\n", str);
	return (EXIT_FAILURE);
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

	atexit(leak);
	if (check_args(argc, argv) == 0)
		return (ft_error("invalid arguments", NULL));
	phil = create_table(ft_atoi(argv[1]), get_data(argc, argv));
	if (!phil)
		return (EXIT_FAILURE);
	// print_table(phil);
	start_threads(&phil);
	return (0);
}
