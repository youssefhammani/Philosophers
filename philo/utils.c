/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhammani <yhammani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 08:29:55 by yhammani          #+#    #+#             */
/*   Updated: 2022/05/28 08:39:31 by yhammani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

int	ft_sleep(long s_time, t_philo *ph)
{
	long	sleep_start;
	long	current_time;

	sleep_start = get_time();
	current_time = sleep_start;
	while (sleep_start + s_time > current_time)
	{
		if (*(ph->alive) == false)
			return (1);
		if (ph->param->time_to_die < (current_time - ph->param->start_time
				- ph->last_meal))
		{
			pthread_mutex_lock(ph->death);
			printer(ph, DEAD);
			*(ph->alive) = false;
			pthread_mutex_unlock(ph->death);
			return (1);
		}
		usleep(150);
		current_time = get_time();
	}
	return (0);
}

int	free_data(t_philo *ph)
{
	int	i;
	int	philo;

	i = 0;
	philo = ph[0].param->philos_nbr;
	while (i < philo)
	{
		if (ph[i].right_fork != NULL)
			free(ph[i].right_fork);
		i++;
	}
	if (ph->alive != NULL)
		free(ph->alive);
	if (ph->print != NULL)
		free(ph->print);
	if (ph->death != NULL)
		free(ph->death);
	if (ph != NULL)
		free(ph);
	return (0);
}
