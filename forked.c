/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forked.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 20:30:16 by alvina            #+#    #+#             */
/*   Updated: 2023/04/18 18:11:57 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_tab_fork(t_fork **fork, t_everything *eth)
{
	int	i;

	i = -1;
	while (++i < eth->philosopher)
	{
		pthread_mutex_destroy(&(fork[i]->fork));
		free(fork[i]);
	}
	free(fork);
}

int	what_the_fork(int num, int lock, t_everything *eth)
{
	static t_fork	**fork;

	if (lock == -1)
	{
		fork = tab_fork_init(eth);
		return (0);
	}
	if (lock == -2)
	{
		free_tab_fork(fork, eth);
		return (0);
	}
	if (lock)
	{
		if (!pthread_mutex_lock(&(fork[num - 1]->fork)))
			return (1);
	}
	else
	{
		if (!pthread_mutex_unlock(&(fork[num - 1]->fork)))
			return (0);
	}
	return (0);
}