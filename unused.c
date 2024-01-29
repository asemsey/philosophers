/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unused.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:24:28 by asemsey           #+#    #+#             */
/*   Updated: 2024/01/29 15:25:07 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// array of philosopers with neighbours, life and state. no thread yet!
t_philo	*get_phil(int life, int count)
{
	int		i;
	t_philo	**phil;

	i = 0;
	phil = (t_philo	**)malloc(sizeof(t_philo *) * (count + 1));
	if (!phil)
		return (NULL);
	while (i < count)
	{
		phil[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!phil[i])
			return (ft_error(NULL, phil));
		phil[i]->left = i;
		if (i == 0)
			phil[i]->left = count;
		phil[i]->name = i + 1;
		phil[i]->right = i + 2;
		if (i + 2 > count)
			phil[i]->right = 1;
		phil[i]->life = life;
		phil[i]->state = 0;
		i++;
	}
	phil[i] = NULL;
	return (phil);
}

void	print_philo(t_philo **phil)
{
	int	i;

	i = 0;
	if (!phil)
		return ;
	printf("left  name  right || state  life\n");
	printf("--------------------------------\n");
	while (phil[i])
	{
		printf("%d     %d     %d     || %d      %d\n", phil[i]->left,\
			phil[i]->name, phil[i]->right, phil[i]->state, phil[i]->data->life_time);
		i++;
	}
	printf("--------------------------------\n");
}
