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
	if (!philo->is_dead && philo->sim->eos < philo->sim->nbr_philo)
	{
		if (msg[3] == 'e' && philo->sim->nbr_meals != 0)
			printf("%*ld %d %s his %d meal\n", SPACE, get_time()
				- philo->start_time, philo->id, msg, philo->count_meal);
		else
			printf("%*ld %d %s\n", SPACE, get_time() - philo->start_time,
				philo->id, msg);
	}
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
}

void	*ft_reaper(void *arg)
{
	t_arg	*sim;

	sim = (t_arg *)arg;
	while (sim->eos < sim->nbr_philo)
	{
		while (sim->philo)
		{
			if (!sim->philo->is_dead
				&& get_time() - sim->philo->last_meal > sim->time_to_die)
			{
				pthread_mutex_lock(&sim->print);
				sim->eos = sim->nbr_philo;
				printf("%*ld %d died\n", SPACE,
					get_time() - sim->philo->start_time, sim->philo->id);
				sim->philo->is_dead = 1;
				pthread_mutex_unlock(&sim->print);
				break ;
			}
			sim->philo = sim->philo->next;
		}
		sim->philo = sim->head;
	}
	return (NULL);
}

void	ft_routine(t_philo	*philo)
{
	eating(philo);
	ft_print(philo, "is sleeping");
	waiting(philo, philo->sim->time_to_sleep);
	ft_print(philo, "is thinking");
	philo->count_meal++;
}

void	*init_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->start_time = get_time();
	philo->last_meal = philo->start_time;
	if (philo->id % 2 == 1)
		waiting(philo, philo->sim->time_to_eat / 2);
	while ((philo->count_meal <= philo->sim->nbr_meals
			|| philo->sim->nbr_meals == 0) && !philo->is_dead
		&& philo->sim->eos < philo->sim->nbr_philo)
	{
		if (philo->sim->head == philo->sim->tail)
		{
			ft_print(philo, "has taken a fork");
			waiting(philo, philo->sim->time_to_die + 1);
			philo->sim->eos++;
			philo->is_dead = 1;
			return (NULL);
		}
		else
			ft_routine(philo);
	}
	philo->sim->eos++;
	philo->is_dead = 1;
	return (NULL);
}
