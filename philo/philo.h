/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 10:27:50 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/21 15:51:50 by asemsey          ###   ########.fr       */
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
	int				all_ready;
	time_t			start;
	int				life_time;
	int				eat_time;
	int				sleep_time;
	int				min_meals;
	int				end_sim;
	pthread_mutex_t	m_var;
	pthread_mutex_t	m_die;
	pthread_mutex_t	m_print;
}	t_data;

typedef struct s_fork
{
	pthread_mutex_t	m_fork;
	int				name;
	int				locked;
}	t_fork;

typedef struct s_philo	t_philo;
// state: 0-sleep 1-eat 2-think
struct s_philo
{
	t_data		*data;
	pthread_t	id;
	int			name;
	t_philo		*left;
	t_philo		*right;
	t_fork		*l_fork;
	t_fork		*r_fork;
	int			t_since_think;
	int			is_eating;
	int			meals;
	long int	last_meal;
};

// init:

int			check_args(int argc, char **argv);
void		start_threads(t_philo **phil);

// simulation loop

void		*live(void *param);
void		monitor_status(t_philo *phil);
void		thinking(t_philo *phil, int ms, int alone);
void		eating(t_philo *phil);
void		sleeping(t_philo *phil);
void		ft_status(t_philo *phil, int state);

// struct funcs:

t_data		*get_data(int argc, char **argv);
t_philo		*create_table(int count, t_data *data);
t_philo		*highest(t_philo *phil);
void		create_forks(t_philo **phil);
void		free_philo(t_philo **phil);

// utils

int			ft_atoi(const char *str);
int			get_int(int *var, pthread_mutex_t *mutex);
long int	get_long(long int *var, pthread_mutex_t *mutex);
void		set_int(int *var, int value, pthread_mutex_t *mutex);
void		set_long(long int *var, long int value, pthread_mutex_t *mutex);
void		increment_int(int *var, pthread_mutex_t *mutex);

long int	ft_timeofday(void);
long int	get_utimestamp(long int start);
long int	get_timestamp(long int start);
void		ft_usleep(long int us, int *end, pthread_mutex_t *m_die);
void		ft_msleep(long int ms, int *end, pthread_mutex_t *m_die);

#endif