/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 09:07:46 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/06/08 09:07:48 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_arg(t_arg *arg, char **av)
{
	int	ret;

	ret = 0;
	ret = check_arg(av);
	if (ret)
		return (ret);
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
		printf("\033[0;3%dm init_thread_id %d\033[0m\n", sim->philo->id, sim->philo->id);
		check = pthread_create(&sim->philo->thread, NULL, &ft_routine, (void *)sim);
		if (check != 0)
			return (8);
		// remove join
		sim->philo = sim->philo->next;
	}
	sim->philo = sim->head;
//	while (sim->philo)
//	{
//		pthread_join(sim->philo->thread, NULL);
//		sim->philo = sim->philo->next;
//	}
//	sim->philo = sim->head;
	return (0);
}