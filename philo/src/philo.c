/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:06:13 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/06/15 21:27:18 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo	*philo, char *msg)
{
	pthread_mutex_lock(&philo->sim->print);
	if (get_time() - philo->last_meal > philo->sim->time_to_die)
		philo->is_dead = 1;
	else if (!philo->is_dead && !philo->sim->eos)
		printf("%*ld %d %s\n", SPACE, get_time() - philo->start_time,
			philo->id, msg);
	pthread_mutex_unlock(&philo->sim->print);
}

void	eating(t_philo	*philo)
{
	pthread_mutex_lock(&philo->fork);
	ft_print(philo, "has taken a fork");
	if (philo == philo->sim->tail)
		pthread_mutex_lock(&philo->sim->head->fork);
	else
		pthread_mutex_lock(&philo->next->fork);
	ft_print(philo, "has taken a fork");
	ft_print(philo, "is eating");
	philo->last_meal = get_time();
	waiting(philo, philo->sim->time_to_eat);
	pthread_mutex_unlock(&philo->fork);
	if (philo == philo->sim->tail)
		pthread_mutex_unlock(&philo->sim->head->fork);
	else
		pthread_mutex_unlock(&philo->next->fork);
	philo->count_meal++;
}

void	*ft_reaper(void *arg)
{
	t_arg	*sim;

	sim = (t_arg *)arg;
	while (!sim->eos)
	{
		while (sim->philo)
		{
			pthread_mutex_lock(&sim->print);
			if (sim->philo->is_dead
				|| get_time() - sim->philo->last_meal > sim->time_to_die)
			{
				sim->eos = 1;
				printf("%*ld %d died\n", SPACE,
					get_time() - sim->philo->start_time, sim->philo->id);
			}
			pthread_mutex_unlock(&sim->print);
			sim->philo = sim->philo->next;
		}
		sim->philo = sim->head;
	}
	exit (EXIT_FAILURE);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->start_time = get_time();
	philo->last_meal = philo->start_time;
	while ((philo->count_meal < philo->sim->nbr_meals || !philo->sim->nbr_meals)
		&& !philo->is_dead)
	{
		if (philo->id % 2 == 1)
			usleep(philo->sim->time_to_eat);
		if (philo->sim->head == philo->sim->tail)
		{
			ft_print(philo, "has taken a fork");
			waiting(philo, philo->sim->time_to_die + 1);
			return (NULL);
		}
		else
			eating(philo);
		ft_print(philo, "is sleeping");
		waiting(philo, philo->sim->time_to_sleep);
		ft_print(philo, "is thinking");
	}
	return (NULL);
}
