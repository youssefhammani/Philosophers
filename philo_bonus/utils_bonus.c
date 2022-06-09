/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhammani <yhammani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 08:31:55 by yhammani          #+#    #+#             */
/*   Updated: 2022/05/31 22:20:48 by yhammani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

void	ft_sleep(long s_time, t_philo *ph)
{
	long	sleep_start;
	long	current_time;

	sleep_start = get_time();
	current_time = sleep_start;
	while (sleep_start + s_time > current_time)
	{
		if (ph->param->time_to_die < (current_time - ph->param->start_time
				- ph->last_meal))
		{
			sem_wait(ph->param->death);
			printer(ph, DEAD);
			sem_close(ph->param->print);
			sem_close(ph->param->forks);
			sem_close(ph->param->death);
			sem_unlink("forks_s");
			sem_unlink("print_s");
			sem_unlink("death_s");
			exit(EXIT_FAILURE);
		}
		usleep(150);
		current_time = get_time();
	}
}
