/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:06:13 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/05/11 11:06:21 by tpinto-m         ###   ########.fr       */
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

void	error_msg(char *str)
{
	put_str(str);
	exit(EXIT_FAILURE);
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

int	main(int ac, char **av)
{
	if (ac > 6 || ac < 5)
		error_msg("bad arguments\n");
	(void)av;
	return (EXIT_SUCCESS);
}
