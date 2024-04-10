/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 10:26:38 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/10 16:39:55 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 1:[number_of_philosophers]
// 2:[time_to_die]
// 3:[time_to_eat]
// 4:[time_to_sleep]
// optional: 5:[number_of_times_each_philosopher_must_eat]
int	main(int argc, char **argv)
{
	t_philo		*phil;

	if (check_args(argc, argv) == 0)
	{
		printf("Error\ninvalid arguments\n");
		return (EXIT_FAILURE);
	}
	phil = create_table(ft_atoi(argv[1]), get_data(argc, argv));
	if (!phil)
		return (EXIT_FAILURE);
	start_threads(&phil);
	return (EXIT_SUCCESS);
}

// ./philo 7 800 200 200 20 > output1.txt