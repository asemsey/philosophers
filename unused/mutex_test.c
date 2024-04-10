/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 10:46:03 by asemsey           #+#    #+#             */
/*   Updated: 2024/02/04 11:04:52 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

struct s_meow
{
	int				cats;
	pthread_mutex_t	mutex;
};

void	*ft_increment(void *param)
{
	struct s_meow	*m;

	m = param;
	for (int i = 0; i < 5; i++)
	{
		pthread_mutex_lock(&(m->mutex));
		printf("lock\n");
		m->cats++;
		printf("%d\n", m->cats);
		pthread_mutex_unlock(&(m->mutex));
		printf("unlock\n");
	}
	return (m);
}

int main(void)
{
	struct s_meow *m;
	pthread_t	a = NULL;
	pthread_t	b = NULL;
	pthread_t	c = NULL;

	m = malloc(sizeof(struct s_meow));
	if (!m)
	{
		printf("fail\n");
		return (1);
	}
	m->cats = 0;
	pthread_mutex_init(&(m->mutex), NULL);
	pthread_create(&a, NULL, ft_increment, (void *)m);
	pthread_create(&b, NULL, ft_increment, (void *)m);
	pthread_create(&c, NULL, ft_increment, (void *)m);

	pthread_join(a, NULL);
	pthread_join(b, NULL);
	pthread_join(c, NULL);
	printf("result: %d\n", m->cats);
	return 0;
}
