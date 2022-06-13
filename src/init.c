/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 09:07:46 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/06/14 00:00:35 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_digit(char	**av)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
		{
			if (!ft_isdigit(av[i][j]))
				return (7);
		}
	}
	return (0);
}

int	set_arg(t_arg *arg, char **av)
{
	int	ret;

	ret = 0;
	ret = check_digit(av);
	arg->nbr_philo = ft_atoi(av[1]);
	if (arg->nbr_philo <= 0)
		ret = 1;
	arg->time_to_die = ft_atoi(av[2]);
	if (arg->time_to_die <= 0)
		ret = 2;
	arg->time_to_eat = ft_atoi(av[3]);
	if (arg->time_to_eat <= 0)
		ret = 3;
	arg->time_to_sleep = ft_atoi(av[4]);
	if (arg->time_to_sleep <= 0)
		ret = 4;
	arg->nbr_meals = 0;
	if (av[5])
		arg->nbr_meals = ft_atoi(av[5]);
	if (arg->nbr_meals < 0)
		ret = 5;
	return (ret);
}

int	init_philo(t_arg *sim)
{
	int		id;

	sim->philo = NULL;
	id = -1;
	while (++id < sim->nbr_philo)
		append(&sim->philo, id);
	sim->head = sim->philo;
	while (sim->philo)
		sim->philo = sim->philo->next;
	sim->tail = sim->philo;
	sim->philo = sim->head;
	return (0);
}

int	init_fork(t_arg *sim)
{
	if (pthread_mutex_init(&sim->prt, NULL) != 0)
		return (9);
	while (sim->philo)
	{
		if (pthread_mutex_init(&sim->philo->fork, NULL) != 0)
			return (9);
		sim->philo = sim->philo->next;
	}
	sim->philo = sim->head;
	return (0);
}

int	init_thread(t_arg *sim)
{
	int		check;

	while (sim->philo)
	{
		check = pthread_create(&sim->philo->thread, NULL,
				&ft_routine, (void *)sim);
		if (check != 0)
			return (8);
		pthread_join(sim->philo->thread, NULL);
		sim->philo = sim->philo->next;
	}
	sim->philo = sim->head;
	return (0);
}
