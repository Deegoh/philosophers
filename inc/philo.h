/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:06:25 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/06/06 15:36:24 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <stdio.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	fork;
	struct s_philo	*next;
	struct s_philo	*prev;
}	t_philo;

typedef struct s_arg
{
	int		nbr_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nbr_meals;
	t_philo	*philo;
}	t_arg;

#endif