/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forked.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 20:30:16 by alvina            #+#    #+#             */
/*   Updated: 2023/03/10 20:26:32 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	what_the_fork(int num, int lock, t_everything *eth)
{
	static t_fork	**fork;

	if (lock == -1)
	{
		fork = tab_fork_init(eth);
		return (0);
	}
	if (lock)
	{
		if (!pthread_mutex_lock(&(fork[num - 1]->fork)))
		{
			printf("forked %d taken\n", num);
			return (1);
		}
	}
	else
	{
		if (!pthread_mutex_unlock(&(fork[num - 1]->fork)))
		{
			printf("forked %d freed\n", num);
			return (0);
		}
	}
	return (0);
}