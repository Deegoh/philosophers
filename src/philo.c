/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:06:13 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/05/12 16:55:36 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	put_char(char c)
{
	write(1, &c, 1);
}

size_t	put_str(char *str)
{
	return (write(1, str, ft_strlen(str)));
}

void	put_nbr(int nbr)
{
	long	l_nbr;

	l_nbr = nbr;
	if (l_nbr > INT_MAX || l_nbr < INT_MIN)
		return ;
	if (l_nbr < 0)
	{
		put_char('-');
		l_nbr = -l_nbr;
		put_nbr((int)l_nbr);
	}
	else if (l_nbr <= 9)
		put_char((int)l_nbr + '0');
	else
	{
		put_nbr((int)l_nbr / 10);
		put_nbr((int)l_nbr % 10);
	}
}

int	check_arg(char **av)
{
	int	i;

	i = -1;
	while (av[++i])
		if (atol(av[i]) > INT_MAX)
			return (7);
	return (0);
}

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

void	error_display(int error)
{
	if (error == 1)
		printf("Should have more philo\n");
	else if (error == 2)
		printf("Time to die should be superor to zero\n");
	else if (error == 3)
		printf("Time to eat should be superor to zero\n");
	else if (error == 4)
		printf("Time to sleep should be superor to zero\n");
	else if (error == 5)
		printf("Number of meals should be positive\n");
	else if (error == 6)
		printf("bad arguments\n");
	else if (error == 7)
		printf("Value is over max int\n");
}

void	append(t_philo **head_ref, int id)
{
	t_philo	*new_node;
	t_philo	*last;

	new_node = (t_philo *)malloc(sizeof(t_philo));
	new_node->id = id;
	new_node->next = NULL;
	if (*head_ref == NULL)
	{
		new_node->prev = NULL;
		*head_ref = new_node;
		return ;
	}
	last = *head_ref;
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
	return ;
}

void	init_sim(t_arg *sim)
{
	int	id;

	// sim->philo = malloc(sizeof(t_philo) * sim->nbr_philo);
	sim->philo = NULL;
	id = -1;
	while (++id < sim->nbr_philo)
		append(&sim->philo, id);
}

int	main(int ac, char **av)
{
	t_arg		sim;
	int			check;

	check = 0;
	if (ac > 6 || ac < 5)
		check = 6;
	if (!check)
		check = set_arg(&sim, av);
	if (!check)
	{
		init_sim(&sim);
		while (sim.philo)
		{
			printf("id[%d]\n", sim.philo->id);
			sim.philo = sim.philo->next;
		}
		return (EXIT_SUCCESS);
	}
	error_display(check);
	return (EXIT_FAILURE);
}
