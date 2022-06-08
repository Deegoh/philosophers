/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:06:13 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/06/06 17:58:05 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_arg	*sim)
{
	printf("%d has taken forks\n", sim->philo->id);
}

void	eat(t_arg	*sim)
{
	sim->philo->count_meal++;
	printf("meal %d\n", sim->philo->count_meal);
	take_forks(sim);
	printf("%d has taken forks\n", sim->philo->id);
	printf("%d is eating\n", sim->philo->id);
	usleep(100000);
}

// may be routine
void	*ft_routine(void *arg)
{
	t_arg	*sim;

	sim = (t_arg *)arg;
	while ((sim->philo->count_meal < sim->nbr_meals || !sim->nbr_meals)
		&& !sim->philo->is_dead)
	{
		if (sim->philo->id % 2 == 0)
			usleep(100);
		eat(sim);
	//	sleep();
	//	think();
	//	printf("%d is sleeping\n", sim->philo->id);
	//	printf("%d is thinking\n", sim->philo->id);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_arg		*sim;
	int			check;

	check = 0;
	if (ac > 6 || ac < 5)
		check = 6;
	sim = malloc(sizeof(t_arg));
	if (!sim)
		check = 10;
	if (!check)
		check = set_arg(sim, av);
	if (!check)
		check = init_philo(sim);
	if (!check)
		check = init_fork(sim);
	if (!check)
		check = init_thread(sim);
	free_all(sim);
	if (check)
		return (EXIT_SUCCESS);
	error_display(check);
	return (EXIT_FAILURE);
}
