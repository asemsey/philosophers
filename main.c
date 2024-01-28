/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 10:26:38 by asemsey           #+#    #+#             */
/*   Updated: 2024/01/28 15:31:07 by asemsey          ###   ########.fr       */
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

// [number_of_philosophers]  [time_to_die]  [time_to_eat]  [time_to_sleep]
// optional: [number_of_times_each_philosopher_must_eat]
int main(int argc, char **argv)
{
	int			i;
	t_philo		**phil;

	i = check_args(argc, argv);
	if (i == 0)
		return (ft_error("invalid arguments", NULL));
	phil = get_phil(ft_atoi(argv[2]), ft_atoi(argv[1]));
	if (!phil)
		return (EXIT_FAILURE);
	get_data(argc, argv, phil);
	print_philo(phil);
	return (0);
}

// pthread_create(&a, NULL, get_s, (void *)&c);
// pthread_create(&b, NULL, get_v, (void *)&c);
// pthread_join(a, NULL);
// pthread_join(b, NULL);