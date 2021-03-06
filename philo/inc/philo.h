/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:06:25 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/06/13 23:19:57 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <stdio.h>
# include <sys/time.h>

# define SPACE 7

typedef struct s_philo
{
	int				id;
	int				is_dead;
	int				count_meal;
	size_t			start_time;
	size_t			last_meal;
	pthread_t		thread;
	pthread_mutex_t	fork;
	struct s_philo	*next;
	struct s_philo	*prev;
	struct s_arg	*sim;
}	t_philo;

typedef struct s_arg
{
	int				nbr_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				nbr_meals;
	int				eos;
	pthread_t		reaper;
	pthread_mutex_t	print;
	t_philo			*philo;
	t_philo			*head;
	t_philo			*tail;
}	t_arg;

void	waiting(t_philo *philo, size_t time);
size_t	get_time(void);
void	append(t_philo **head_ref, int id);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);

void	error_display(int error);
void	free_all(t_arg *sim);

int		set_arg(t_arg *arg, char **av);
int		init_sim(t_arg *sim);
int		init_mutex(t_arg *sim);
int		init_thread(t_arg *sim);

void	*init_philo(void *arg);
void	*ft_reaper(void *arg);
void	ft_routine(t_philo	*philo);

#endif