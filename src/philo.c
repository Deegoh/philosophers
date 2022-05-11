/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:06:13 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/05/11 17:16:23 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	put_char(char c)
{
	write(1, &c, 1);
}

size_t	put_str(char *str)
{
	return (write(1, str, ft_strlen(str)));
}

void	put_nbr(int nbr)
{
	long	l_nbr;

	l_nbr = nbr;
	if (l_nbr > INT_MAX || l_nbr < INT_MIN)
		return ;
	if (l_nbr < 0)
	{
		put_char('-');
		l_nbr = -l_nbr;
		put_nbr((int)l_nbr);
	}
	else if (l_nbr <= 9)
		put_char((int)l_nbr + '0');
	else
	{
		put_nbr((int)l_nbr / 10);
		put_nbr((int)l_nbr % 10);
	}
}

int	set_arg(t_arg *arg, char **av)
{
	int	ret;

	ret = 0;
	arg->nbr_philo = atoi(av[1]);
	if (arg->nbr_philo <= 0)
		ret = 1;
	arg->time_to_die = atoi(av[2]);
	if (arg->time_to_die <= 0)
		ret = 2;
	arg->time_to_eat = atoi(av[3]);
	if (arg->time_to_eat <= 0)
		ret = 3;
	arg->time_to_sleep = atoi(av[4]);
	if (arg->time_to_sleep <= 0)
		ret = 4;
	arg->nbr_meals = 0;
	if (av[5])
		arg->nbr_meals = atoi(av[5]);
	if (arg->nbr_meals < 0)
		ret = 5;
	return (ret);
}

int	main(int ac, char **av)
{
	t_arg		arg;
	pthread_t	philo;

	if (ac > 6 || ac < 5)
	{
		printf("bad arguments\n");
		return (EXIT_FAILURE);
	}
	if (!set_arg(&arg, av))
	{
		set_arg(&arg, av);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
