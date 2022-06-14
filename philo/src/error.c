/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 09:11:35 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/06/13 23:21:31 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_display(int error)
{
	if (error == 1)
		printf("Should have more philo\n");
	else if (error == 2)
		printf("Time to die should be between 1 and 2147483647\n");
	else if (error == 3)
		printf("Time to eat should be between 1 and 2147483647\n");
	else if (error == 4)
		printf("Time to sleep should be between 1 and 2147483647\n");
	else if (error == 5)
		printf("Number of meals should be between 1 and 2147483647\n");
	else if (error == 6)
		printf("bad arguments\n");
	else if (error == 7)
		printf("Arguments isn't digits\n");
	else if (error == 8)
		printf("Thread error\n");
	else if (error == 9)
		printf("Mutex error\n");
	else if (error == 10)
		printf("Malloc error\n");
}

void	free_all(t_arg *sim)
{
	sim->philo = sim->head;
	while (sim->philo && sim->philo->next)
	{
		pthread_mutex_destroy(&sim->philo->fork);
		sim->philo = sim->philo->next;
		free(sim->philo->prev);
	}
	pthread_mutex_destroy(&sim->stop);
	free(sim->philo);
	free(sim);
}
