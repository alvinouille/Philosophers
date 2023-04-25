/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:25:29 by alvina            #+#    #+#             */
/*   Updated: 2023/04/25 19:59:10 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_everything	*eth_object(int ac, char **av)
{
	static t_everything	*eth;

	if (ac == 0)
		return (eth);
	eth = malloc(sizeof(t_everything));
	if (!eth)
		return (NULL);
	if (!eth_supp(&eth, ac, av))
		return (free(eth), NULL);
	if (pthread_mutex_init(&(eth->finish), NULL))
		return (free(eth), NULL);
	if (pthread_mutex_init(&(eth->msg), NULL))
	{
		pthread_mutex_destroy(&(eth->finish));
		return (free(eth), NULL);
	}
	return (eth);
}

t_philo	*philo_init(int num, t_everything *eth)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->eth = eth;
	new->num = num;
	new->fork_one = 0;
	new->fork_two = 0;
	if (pthread_mutex_init(&(new->mealing), NULL))
		return (free(new), NULL);
	new->state = 2;
	new->meals = 0;
	new->has_eaten = get_time();
	return (new);
}

t_philo	**tab_philo_init(int nb, t_everything *eth)
{
	int		i;
	int		j;
	t_philo	**philo;

	i = -1;
	j = 0;
	philo = malloc(sizeof(t_philo *) * nb);
	if (!philo)
		return (eth_clean(eth), NULL);
	while (++i < nb)
	{
		philo[i] = philo_init(i + 1, eth);
		if (!philo[i])
		{
			while (j < i)
			{
				pthread_mutex_destroy(&(philo[j]->mealing));
				free(philo[j]);
				j++;
			}
			return (free(philo), NULL);
		}
	}
	return (philo);
}

t_fork	*fork_init(void)
{
	t_fork	*new;

	new = malloc(sizeof(t_fork));
	if (!new)
		return (NULL);
	pthread_mutex_init(&(new->fork), NULL);
	new->status = 0;
	return (new);
}

t_fork	**tab_fork_init(t_everything *eth)
{
	int		i;
	int		j;
	t_fork	**tab;

	i = -1;
	j = 0;
	tab = malloc(sizeof(t_fork *) * eth->philosopher);
	if (!tab)
		return (NULL);
	while (++i < eth->philosopher)
	{
		tab[i] = fork_init();
		if (!tab[i])
		{
			while (j < i)
			{
				pthread_mutex_destroy(&(tab[j]->fork));
				free(tab[j]);
				j++;
			}
			free(tab);
			return (NULL);
		}
	}
	return (tab);
}
