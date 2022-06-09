/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhammani <yhammani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 08:41:04 by yhammani          #+#    #+#             */
/*   Updated: 2022/05/28 08:41:12 by yhammani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include	<stdlib.h>
# include	<unistd.h>
# include	<sys/time.h>
# include	<pthread.h>
# include	<stdbool.h>
# include	<stdio.h>

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
	int		philos_nbr;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		meals_to_eat;
	long	start_time;
}	t_param;

typedef struct s_philo
{
	t_param			*param;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*print;
	pthread_mutex_t	*death;
	pthread_t		philo_p;
	long			last_meal;
	int				id;
	int				meals_eaten;
	bool			*alive;
}	t_philo;

void	*actions(void *ph);
void	printer(t_philo *ph, int state);
int		join_philo(t_philo *philo, int ph);
t_philo	*create_philo(t_param *param);
int		free_data(t_philo *philo);
int		ft_sleep(long s_time, t_philo *ph);
long	get_time(void);

#endif
