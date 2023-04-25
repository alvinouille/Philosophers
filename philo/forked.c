/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forked.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 20:30:16 by alvina            #+#    #+#             */
/*   Updated: 2023/04/21 18:52:35 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	what_the_fork(int num, int lock, t_everything *eth)
{
	static t_fork	**fork;

	if (lock == -1)
	{
		fork = tab_fork_init(eth);
		if (!fork)
			return (0);
		return (1);
	}
	if (lock == -2)
	{
		free_tab_fork(fork, eth);
		return (1);
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

static void	fork_odd(t_philo *philo)
{
	if (!philo->fork_one)
	{
		philo->fork_one = what_the_fork(philo->num, 1, philo->eth);
		if (philo->fork_one)
			print_msg(philo);
	}
	if (!philo->fork_two && philo->eth->philosopher != 1)
	{
		if (philo->num == 1)
			philo->fork_two = what_the_fork(philo->eth->philosopher, 1,
					philo->eth);
		else
			philo->fork_two = what_the_fork(philo->num - 1, 1, philo->eth);
		if (philo->fork_two)
			print_msg(philo);
	}
}

static void	fork_even(t_philo *philo)
{
	if (!philo->fork_one)
	{
		philo->fork_one = what_the_fork(philo->num - 1, 1, philo->eth);
		if (philo->fork_one)
			print_msg(philo);
	}
	if (!philo->fork_two)
	{
		philo->fork_two = what_the_fork(philo->num, 1, philo->eth);
		if (philo->fork_two)
			print_msg(philo);
	}
}

int	taking_forks(t_philo *philo)
{
	while (!philo->fork_one || !philo->fork_two)
	{
		if (philo->num % 2 != 0)
			fork_odd(philo);
		else
			fork_even(philo);
		pthread_mutex_lock(&philo->eth->finish);
		if (philo->eth->ones_dead == 1)
			return (0);
		pthread_mutex_unlock(&philo->eth->finish);
	}
	return (1);
}

void	leaving_forks(t_philo *philo)
{
	if (philo->num == 1)
	{
		if (philo->fork_one)
			philo->fork_one = what_the_fork(philo->eth->philosopher, 0,
					philo->eth);
		if (philo->fork_two)
			philo->fork_two = what_the_fork(philo->num, 0, philo->eth);
	}
	else
	{
		if (philo->fork_one)
			philo->fork_one = what_the_fork(philo->num - 1, 0, philo->eth);
		if (philo->fork_two)
			philo->fork_two = what_the_fork(philo->num, 0, philo->eth);
	}
}
