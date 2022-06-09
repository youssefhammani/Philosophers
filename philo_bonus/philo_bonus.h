/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhammani <yhammani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 08:31:08 by yhammani          #+#    #+#             */
/*   Updated: 2022/05/31 22:20:21 by yhammani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include	<stdlib.h>
# include	<unistd.h>
# include	<pthread.h>
# include	<stdbool.h>
# include	<semaphore.h>
# include	<stdio.h>
# include	<signal.h>
# include	<fcntl.h>
# include	<sys/time.h>
# include	<sys/stat.h>
# include	<sys/types.h>
# include	<sys/wait.h>
# include	<string.h>

typedef enum e_state
{
	TAKEN_FORK	=	1,
	EATING		=	2,
	SLEEPING	=	3,
	THINKING	=	4,
	DEAD		=	5,
}	t_state;

typedef struct s_param
{
	sem_t	*print;
	sem_t	*forks;
	sem_t	*death;
	int		philos_nbr;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		meals_to_eat;
	long	start_time;
}	t_param;

typedef struct s_philo
{
	t_param	*param;
	pid_t	philo_p;
	long	last_meal;
	int		id;
	int		meals_eaten;
}	t_philo;

void		actions(t_philo *philo);
void		create_philo(t_param *param);
long		get_time(void);
void		ft_sleep(long time, t_philo *philo);
size_t		ft_strlen(const char *s);
void		printer(t_philo *philo, int state);
long long	ft_atoi_ll(char *str);

#endif