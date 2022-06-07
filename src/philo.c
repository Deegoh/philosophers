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

void	take_forks(t_arg	*sim)
{
	printf("%d has taken forks\n", sim->philo->id);
}

void	eat(t_arg	*sim)
{
	sim->philo->count_meal++;
	printf("meal %d\n", sim->philo->count_meal);
	take_forks(sim);
//	printf("%d has taken forks\n", sim->philo->id);
	printf("%d is eating\n", sim->philo->id);
//	usleep(100000);
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
//		printf("\033[0;3%dm init_thread_id %d\033[0m\n", sim->philo->id, sim->philo->id);
		check = pthread_create(&sim->philo->thread, NULL, &ft_routine, (void *)sim);
		if (check != 0)
			return (8);
		// remove join
		pthread_join(sim->philo->thread, NULL);
		sim->philo = sim->philo->next;
	}
	sim->philo = sim->head;
	return (0);
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
	{
		sim->philo->count_meal = 0;
		sim->philo->is_dead = 0;
		sim->philo = sim->philo->next;
	}
	sim->philo = sim->head;
	return (0);
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
