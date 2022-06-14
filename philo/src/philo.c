/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:06:13 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/06/13 23:59:49 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo	*philo, char *msg)
{
	if (get_time() - philo->last_meal > (size_t)philo->sim->time_to_die)
	{
		philo->is_dead = 1;
		pthread_mutex_lock(&philo->sim->stop);
		printf("%*ld %d %s\n", SPACE,
			get_time() - philo->start_time, philo->id, msg);
		usleep(1000);
		free_all(philo->sim);
		exit(1);
	}
	else if (!philo->is_dead)
		printf("%*ld %d %s\n", SPACE, get_time() - philo->start_time,
			philo->id, msg);
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
	waiting(philo, (size_t)philo->sim->time_to_eat);
	pthread_mutex_unlock(&philo->fork);
	if (philo == philo->sim->tail)
		pthread_mutex_unlock(&philo->sim->head->fork);
	else
		pthread_mutex_unlock(&philo->next->fork);
	philo->count_meal++;
}

void	*ft_reaper(void *arg)
{
	t_arg *sim;

	sim = (t_arg *)arg;
	while (1)
	{
		while (sim->philo)
		{
			if (sim->philo->is_dead)
			{
				pthread_mutex_lock(&sim->stop);
				printf("%*ld %d is died reaper\n", SPACE,
					get_time() - sim->philo->start_time, sim->philo->id);
				usleep(1000);
				free_all(sim);
				exit(1);
			}
			sim->philo = sim->philo->next;
		}
		sim->philo = sim->head;
	}
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
		eating(philo);
		ft_print(philo, "is sleeping");
		waiting(philo, (size_t)philo->sim->time_to_sleep);
		ft_print(philo, "is thinking");
	}
	return (NULL);
}
