/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 19:18:34 by ale-sain          #+#    #+#             */
/*   Updated: 2023/04/25 19:23:13 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arg_checker(long nb)
{
	if (nb == -1 || nb > 2147483647)
		return (0);
	return (1);
}

void	eth_supp(t_everything **eth, char **av)
{
	(*eth)->departure = 0;
	(*eth)->ones_dead = 0;
	(*eth)->all_meal = 0;
	(*eth)->stop_meal = 0;
	pthread_mutex_init(&((*eth)->finish), NULL);
	pthread_mutex_init(&((*eth)->msg), NULL);
	(*eth)->time_to_die = ft_atoll(av[2]);
	(*eth)->time_to_eat = ft_atoll(av[3]);
	(*eth)->time_to_sleep = ft_atoll(av[4]);
}
