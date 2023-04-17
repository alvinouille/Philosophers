/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:25:29 by alvina            #+#    #+#             */
/*   Updated: 2023/04/17 19:17:27 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_everything	*eth_object(int ac, char **av)
{
	static t_everything *eth;

	if (ac == 0)
		return (eth);
	eth = malloc(sizeof(t_everything));
	eth->philosopher = (int)ft_atoll(av[1]);
	eth->fork = eth->philosopher;
	eth->departure = 0;
	eth->ones_dead = 0;
	eth->enough_meal = 0;
    pthread_mutex_init(&(eth->finish), NULL);
	pthread_mutex_init(&(eth->msg), NULL);
	eth->time_to_die = ft_atoll(av[2]);
	eth->time_to_eat = ft_atoll(av[3]);
	eth->time_to_sleep = ft_atoll(av[4]);
	if (ac == 6)
		eth->nb_meal = (int)ft_atoll(av[5]);
	else
		eth->nb_meal = 0;
	return (eth);
}


t_philo	*philo_init(int num, t_everything *eth)
{
	t_philo *new;
	pthread_t p;
	pthread_mutex_t fork;

	new = malloc(sizeof(t_philo));
	new->eth = eth;
	new->num = num;
	new->thread = p;
	new->fork_one = 0;
	new->fork_two = 0;
	new->state = -1;
	new->meals = 0;
	new->has_eaten = get_time();
	return (new);
}

t_philo	**tab_philo_init(int nb, t_everything *eth)
{
	int		i;
	t_philo	**philo;

	i = 0;
	philo = malloc(sizeof(t_philo *) * nb);
	while (i < nb)
	{
		philo[i] = philo_init(i + 1, eth);
		i++;
	}
	return (philo);	
}

t_fork	*fork_init(void)
{
	t_fork *new;

	new = malloc(sizeof(t_fork));
	pthread_mutex_init(&(new->fork), NULL);
	new->status = 0;
	return (new);
}

t_fork **tab_fork_init(t_everything *eth)
{
	int		i;
	t_fork	**tab;

	i = 0;
	tab = malloc(sizeof(t_fork *) * eth->philosopher);
	while (i < eth->philosopher)
	{
		tab[i] = fork_init();
		i++;
	}
	return (tab);
}