/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 10:27:50 by asemsey           #+#    #+#             */
/*   Updated: 2024/01/28 15:32:22 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

/*		allowed:
	memset printf write
	malloc free
	usleep gettimeofday
	pthread_create pthread_join pthread_detach
	pthread_mutex_init pthread_mutex_destroy
	pthread_mutex_lock pthread_mutex_unlock
*/

typedef struct s_data
{
	int		life_time;
	int		eat_time;
	int		sleep_time;
	int		min_meals;
}	t_data;

// state: 0-sleep 1-eat 2-think
typedef struct s_philo
{
	t_data		*data;
	pthread_t	id;
	int			name;
	int			life;
	int			state;
	int			left;
	int			right;
}	t_philo;

// init
int		ft_error(char *str, t_philo **phil);
int		check_args(int argc, char **argv);
t_philo	**get_phil(int life, int count);
void	get_data(int argc, char **argv, t_philo **phil);
void	print_philo(t_philo **phil);

// libft
void	*free_all(void **x);
int		ft_atoi(const char *str);

#endif