/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 09:11:35 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/06/08 09:11:37 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg(char **av)
{
	int	i;

	i = -1;
	while (av[++i])
		if (atol(av[i]) > INT_MAX)
			return (7);
	return (0);
}

void	error_display(int error)
{
	if (error == 1)
		printf("Should have more philo\n");
	else if (error == 2)
		printf("Time to die should be superior to zero\n");
	else if (error == 3)
		printf("Time to eat should be superior to zero\n");
	else if (error == 4)
		printf("Time to sleep should be superior to zero\n");
	else if (error == 5)
		printf("Number of meals should be positive\n");
	else if (error == 6)
		printf("bad arguments\n");
	else if (error == 7)
		printf("Value is over max int\n");
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
		sim->philo = sim->philo->next;
		free(sim->philo->prev);
	}
	free(sim->philo);
	free(sim);
}
