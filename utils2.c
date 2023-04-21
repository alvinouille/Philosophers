/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 19:20:47 by alvina            #+#    #+#             */
/*   Updated: 2023/04/21 19:21:45 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arg_checker(long nb)
{
	if (nb == -1 || nb > 2147483647)
		return (0);
	return (1);
}

void	initialising(t_everything **eth, int nb, char *av)
{
	(*eth)->departure = 0;
	(*eth)->ones_dead = 0;
	(*eth)->all_meal = 0;
	(*eth)->stop_meal = 0;
	pthread_mutex_init(&((*eth)->finish), NULL);
	pthread_mutex_init(&((*eth)->msg), NULL);
	(*eth)->fork = nb;
	(*eth)->time_to_die = ft_atoll(av);
}
