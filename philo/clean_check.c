/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:19:48 by alvina            #+#    #+#             */
/*   Updated: 2023/04/25 18:53:35 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_tab_fork(t_fork **fork, t_everything *eth)
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

void	eth_clean(t_everything *eth)
{
	pthread_mutex_destroy(&(eth->finish));
	pthread_mutex_destroy(&(eth->msg));
	free(eth);
}

void	cleaning(t_philo **philo)
{
	t_everything	*eth;
	int				i;
	int				nb;

	i = 0;
	eth = (t_everything *)(*philo)->eth;
	what_the_fork(0, -2, eth);
	nb = eth->philosopher;
	eth_clean(eth);
	while (i < nb)
	{
		pthread_mutex_destroy(&(philo[i]->mealing));
		free(philo[i]);
		i++;
	}
	free(philo);
}

int	check_mealing(t_philo **philo)
{
	int				i;
	t_everything	*eth;

	eth = (t_everything *)(*philo)->eth;
	if (eth->nb_meal == -1)
		return (1);
	i = -1;
	while (++i < eth->philosopher)
	{
		pthread_mutex_lock(&(philo[i]->mealing));
		if (philo[i]->meals < eth->nb_meal)
		{
			pthread_mutex_unlock(&(philo[i]->mealing));
			return (1);
		}
		pthread_mutex_unlock(&(philo[i]->mealing));
	}
	pthread_mutex_lock(&eth->finish);
	eth->ones_dead = 1;
	pthread_mutex_unlock(&eth->finish);
	return (0);
}

void	death_checker(t_philo **philo)
{
	int				i;
	t_everything	*eth;

	eth = (*philo)->eth;
	while (1)
	{
		i = 0;
		if (!check_mealing(philo))
			return ;
		while (i < eth->philosopher)
		{
			if (master_of_time(philo[i], SINCE_MEAL) > eth->time_to_die)
			{
				pthread_mutex_lock(&eth->finish);
				printf("%ld %d died\n", get_time() - eth->departure,
					philo[i]->num);
				eth->ones_dead = 1;
				pthread_mutex_unlock(&eth->finish);
				return ;
			}
			i++;
		}
		usleep(100);
	}
}
