/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 19:18:34 by ale-sain          #+#    #+#             */
/*   Updated: 2023/04/25 19:59:22 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arg_checker(long nb)
{
	if (nb == -1 || nb > 2147483647)
		return (0);
	return (1);
}

int	eth_supp(t_everything **eth, int ac, char **av)
{
	(*eth)->philosopher = (int)ft_atoll(av[1]);
	if (!arg_checker((*eth)->philosopher))
		return (0);
	(*eth)->fork = (*eth)->philosopher;
	(*eth)->departure = 0;
	(*eth)->ones_dead = 0;
	(*eth)->all_meal = 0;
	(*eth)->stop_meal = 0;
	(*eth)->time_to_die = ft_atoll(av[2]);
	(*eth)->time_to_eat = ft_atoll(av[3]);
	(*eth)->time_to_sleep = ft_atoll(av[4]);
	if (!arg_checker((*eth)->time_to_sleep) || !arg_checker((*eth)->time_to_die)
		|| !arg_checker((*eth)->time_to_eat))
		return (0);
	if (ac == 6)
	{
		(*eth)->nb_meal = (int)ft_atoll(av[5]);
		if (!arg_checker((*eth)->nb_meal))
			return (0);
	}
	else
		(*eth)->nb_meal = -1;
	return (1);
}
