/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 10:27:50 by asemsey           #+#    #+#             */
/*   Updated: 2024/02/14 13:38:47 by asemsey          ###   ########.fr       */
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

typedef struct s_data
{
	time_t			start;
	int				life_time;
	int				eat_time;
	int				sleep_time;
	int				min_meals;
	pthread_mutex_t	m_print;
}	t_data;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				locked;
	int				name;
}	t_fork;

typedef struct s_philo t_philo;
// state: 0-sleep 1-eat 2-think
struct s_philo
{
	t_data		*data;
	pthread_t	id;
	pthread_t	death;
	int			name;
	t_philo		*left;
	t_philo		*right;
	t_fork		*l_fork;
	t_fork		*r_fork;
	int			state;
	int			meals;
	long int	last_meal;
};

// init:

int			ft_error(char *str, t_philo **phil);
int			check_args(int argc, char **argv);
t_data		*get_data(int argc, char **argv);
void		*live(void *param);
// long int	get_start(void);

// t_philo funcs:

t_philo		*create_table(int count, t_data *data);
void		add_to_table(t_philo **phil, t_philo *new);
t_philo		*new_philo(int name, t_data *data);
int			tablesize(t_philo *phil);
t_philo		*highest(t_philo *phil);
void		print_table(t_philo *phil);
void		ft_status(t_philo *phil, int state);
void		free_philo(t_philo **phil);

// t_fork funcs

void		create_forks(t_philo **phil);
void		all_forks(t_philo **phil);
void		add_fork(t_philo **phil, t_fork *new);
t_fork		*new_fork(int name);
void		init_mutexes(t_philo **phil);
void		destroy_mutexes(t_philo **phil);

// libft:

void		*free_all(void **x);
int			ft_atoi(const char *str);

// time

long int	ft_timeofday(void);
long int	get_timestamp(long int start);
void		ft_usleep(long int ms);

#endif