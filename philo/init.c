/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 15:29:02 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/10 16:40:59 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	negative;
	int	res;

	negative = 1;
	res = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			negative *= -1;
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return (negative * res);
}

// 0-fail   1-endless   2-limit
int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5)
		return (0);
	while (i < 5)
	{
		if (i == 1 && ft_atoi(argv[i]) > 200)
			return (0);
		if (ft_atoi(argv[i]) < 1)
			return (0);
		i++;
	}
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) < 1)
			return (0);
		return (2);
	}
	return (1);
}

t_data	*get_data(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->life_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	data->all_ready = 0;
	data->min_meals = 0;
	if (argc == 6)
		data->min_meals = ft_atoi(argv[5]);
	return (data);
}

// create, detach / join threads
void	start_threads(t_philo **phil)
{
	t_philo	*head;

	head = *phil;
	pthread_mutex_init(&(head->data->m_print), NULL);
	pthread_mutex_init(&(head->data->m_var), NULL);
	while (*phil)
	{
		pthread_create(&(*phil)->id, NULL, live, (void *)*phil);
		pthread_detach((*phil)->id);
		if ((*phil)->right == head)
			break ;
		*phil = (*phil)->right;
	}
	*phil = head;
	(*phil)->data->start = ft_timeofday();
	set_int(&(*phil)->data->all_ready, 1, &(*phil)->data->m_var);
	pthread_create(&(*phil)->data->death, NULL, monitor_status, (void *)*phil);
	pthread_join((*phil)->data->death, NULL);
	pthread_mutex_destroy(&(head->data->m_print));
	pthread_mutex_destroy(&(head->data->m_var));
	free_philo(phil);
}
