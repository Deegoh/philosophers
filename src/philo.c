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

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	eating(t_arg	*sim)
{
	size_t	delta;

	pthread_mutex_lock(&sim->philo->fork);
	if (sim->philo == sim->tail)
		pthread_mutex_lock(&sim->head->fork);
	else
		pthread_mutex_lock(&sim->philo->next->fork);
	printf("%*ld %d has taken forks\n", 5,
		get_time() - sim->philo->start_time, sim->philo->id);
	printf("%*ld %d is eating\n", 5,
		get_time() - sim->philo->start_time, sim->philo->id);
	delta = get_time();
	while (1)
	{
		if ((get_time() - delta) >= (size_t)sim->time_to_eat)
			break ;
		usleep(100);
	}
	pthread_mutex_unlock(&sim->philo->fork);
	if (sim->philo == sim->tail)
		pthread_mutex_unlock(&sim->head->fork);
	else
		pthread_mutex_unlock(&sim->philo->next->fork);
	sim->philo->count_meal++;
}

void	sleeping(t_arg	*sim)
{
	size_t	delta;

	pthread_mutex_lock(&sim->prt);
	printf("%*ld %d  is sleeping\n", 5,
		get_time() - sim->philo->start_time, sim->philo->id);
	pthread_mutex_unlock(&sim->prt);
	delta = get_time();
	while (1)
	{
		if ((get_time() - delta) >= (size_t)sim->time_to_sleep)
			break ;
		usleep(100);
	}
}

void	thinking(t_arg	*sim)
{
	pthread_mutex_lock(&sim->prt);
	printf("%*ld %d  is thinking\n", 5,
		get_time() - sim->philo->start_time, sim->philo->id);
	pthread_mutex_unlock(&sim->prt);
}

void	*ft_routine(void *arg)
{
	t_arg	*sim;

	sim = (t_arg *)arg;
	sim->philo->start_time = get_time();
	while ((sim->philo->count_meal < sim->nbr_meals || !sim->nbr_meals)
		&& !sim->philo->is_dead)
	{
		if (sim->philo->id % 2 == 0)
			usleep(1000);
		eating(sim);
		sleeping(sim);
		thinking(sim);
	}
	return (NULL);
}
