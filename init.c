/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:48:11 by alvina            #+#    #+#             */
/*   Updated: 2023/03/08 19:53:04 by alvina           ###   ########.fr       */
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
	eth->start = 0;
	eth->time_to_die = ft_atoll(av[2]);
	eth->time_to_eat = ft_atoll(av[3]);
	eth->time_to_sleep = ft_atoll(av[4]);
	if (ac == 6)
		eth->nb_meal = (int)ft_atoll(av[5]);
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
	new->fork = fork;
	pthread_mutex_init(&(new->fork), NULL);
	new->forks = 0;
	new->state = -1;
	new->is_living = -1;
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
