/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhammani <yhammani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 08:30:39 by yhammani          #+#    #+#             */
/*   Updated: 2022/05/31 22:21:52 by yhammani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	n;

	i = 0;
	s = 1;
	n = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			s = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i++] - 48);
	}
	return (s * n);
}

int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	if (ac != 5 && ac != 6)
		return (printf("Error: Wrong Syntax\n"), 1);
	while (av[i])
	{
		j = 0;
		if (ft_atoi(av[i]) <= 0)
			return (printf("Error: Unvalid arguments\n"), 1);
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (printf("Error: Unvalid arguments\n"), 1);
			j++;
		}
		i++;
	}
	return (0);
}

void	stock_args(t_param *param, int ac, char **av)
{
	param->start_time = get_time();
	param->philos_nbr = ft_atoi(av[1]);
	param->time_to_die = ft_atoi(av[2]);
	param->time_to_eat = ft_atoi(av[3]);
	param->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		param->meals_to_eat = ft_atoi(av[5]);
	else
		param->meals_to_eat = -1;
}

int	main(int ac, char **av)
{
	t_param	param;

	if (check_args(ac, av))
		return (1);
	stock_args(&param, ac, av);
	create_philo(&param);
	return (0);
}
