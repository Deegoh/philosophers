/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 22:44:01 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/06/13 22:44:46 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		check = init_sim(sim);
	if (!check)
		check = init_mutex(sim);
	if (!check)
		check = init_thread(sim);
	if (check > 7 || check == 0)
		free_all(sim);
	if (!check)
		return (EXIT_SUCCESS);
	error_display(check);
	return (EXIT_FAILURE);
}
