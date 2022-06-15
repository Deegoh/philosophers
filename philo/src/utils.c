/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 09:05:28 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/06/13 21:21:05 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	waiting(t_philo *philo, size_t time)
{
	size_t	start;

	start = get_time();
	while (!philo->is_dead)
	{
		if ((get_time() - start) >= time)
			break ;
		usleep(100);
	}
}

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	append(t_philo **head_ref, int id)
{
	t_philo	*new_node;
	t_philo	*last;

	new_node = malloc(sizeof(t_philo));
	new_node->id = id;
	new_node->is_dead = 0;
	new_node->count_meal = 0;
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
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	sign;
	int	count;

	i = 0;
	res = 0;
	sign = 1;
	count = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign *= -1;
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + str[i++] - '0';
		count++;
	}
	if (count > 10 && sign == 1)
		return (sign * -1);
	if (count > 10 && sign == -1)
		return (0);
	return (res * sign);
}
