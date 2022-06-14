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

void	eating(t_philo	*philo)
{
	pthread_mutex_lock(&philo->fork);
	printf("%*ld %d has taken a fork\n", 5,
		get_time() - philo->start_time, philo->id);
	if (philo == philo->sim->tail)
		pthread_mutex_lock(&philo->sim->head->fork);
	else
		pthread_mutex_lock(&philo->next->fork);
	printf("%*ld %d has taken a fork\n", 5,
		get_time() - philo->start_time, philo->id);
	printf("%*ld %d is eating\n", 5,
		get_time() - philo->start_time, philo->id);
	waiting(philo, (size_t)philo->sim->time_to_eat);
	pthread_mutex_unlock(&philo->fork);
	if (philo == philo->sim->tail)
		pthread_mutex_unlock(&philo->sim->head->fork);
	else
		pthread_mutex_unlock(&philo->next->fork);
	philo->count_meal++;
}

void	sleeping(t_philo	*philo)
{
	printf("%*ld %d is sleeping\n", 5,
		get_time() - philo->start_time, philo->id);
	waiting(philo, (size_t)philo->sim->time_to_sleep);
}

void	thinking(t_philo	*philo)
{
	printf("%*ld %d is thinking\n", 5,
		get_time() - philo->start_time, philo->id);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->start_time = get_time();
	while ((philo->count_meal < philo->sim->nbr_meals || !philo->sim->nbr_meals)
		&& !philo->is_dead)
	{
		if (philo->id % 2 == 0)
			usleep(philo->sim->time_to_eat);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
