/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhammani <yhammani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 08:29:41 by yhammani          #+#    #+#             */
/*   Updated: 2022/05/28 08:39:31 by yhammani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fill_philo(t_philo *ph, t_param *param, int i)
{
	while (i < param->philos_nbr)
	{
		ph[i].right_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!ph[i].right_fork || pthread_mutex_init(ph[i].right_fork, NULL))
			return (1);
		i++;
	}
	i = 0;
	while (i < param->philos_nbr)
	{
		ph[i].id = i + 1;
		ph[i].left_fork = ph[(i + 1) % param->philos_nbr].right_fork;
		ph[i].alive = ph[0].alive;
		ph[i].print = ph[0].print;
		ph[i].death = ph[0].death;
		ph[i].param = param;
		ph[i].last_meal = 0;
		ph[i].meals_eaten = 0;
		if (pthread_create(&ph[i].philo_p, NULL, &actions, (void *)&ph[i]))
			return (1);
		i++;
	}
	return (0);
}

t_philo	*create_philo(t_param *param)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo) * (param->philos_nbr));
	philo->alive = (bool *)malloc(sizeof(bool));
	philo->print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	philo->death = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!philo || !philo->alive || !philo->print || !philo->death)
		return (NULL);
	*(philo->alive) = true;
	if (pthread_mutex_init(philo->print, NULL))
		return (NULL);
	if (pthread_mutex_init(philo->death, NULL))
		return (NULL);
	if (fill_philo(philo, param, 0))
		return (NULL);
	return (philo);
}

int	join_philo(t_philo *philo, int ph)
{
	int		i;

	i = 0;
	while (i < ph)
	{
		if (pthread_join(philo[i].philo_p, NULL))
			return (1);
		pthread_mutex_destroy(philo[i].right_fork);
		i++;
	}
	pthread_mutex_destroy(philo->print);
	pthread_mutex_destroy(philo->death);
	return (0);
}

void	printer(t_philo *ph, int state)
{
	pthread_mutex_lock(ph->print);
	printf("%ld\t", get_time() - ph->param->start_time);
	printf("%d", ph->id);
	if (state == TAKEN_FORK)
		printf("\thas taken a fork\n");
	else if (state == EATING)
		printf("\tis eating\n");
	else if (state == SLEEPING)
		printf("\tis sleeping\n");
	else if (state == THINKING)
		printf("\tis thinking\n");
	else if (state == DEAD)
		printf("\tdied\n");
	pthread_mutex_unlock(ph->print);
}
