/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:48:11 by alvina            #+#    #+#             */
/*   Updated: 2023/03/08 11:59:43 by alvina           ###   ########.fr       */
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
	eth->aot = NULL;
	return (eth);
}

t_philo	*philo_init(int num)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	new->num = num;
	pthread_mutex_init(&(new->fork), NULL);
	new->forks = 0;
	new->state = -1;
	new->timestamp = 0;
	new->is_eating = 0;
	new->is_sleeping = 0;
	new->is_living = 0;
	new->alive = 1;
	return (new);
}

t_list	*aot_init(int nb)
{
	int		i;
	t_list	*lst;
	t_list	*new;
	t_philo	*philo;

	i = 0;
	lst = NULL;
	while (++i < nb + 1)
	{
		philo = philo_init(i);
		new = ft_lstnew((t_philo *)philo);
		ft_lstadd_back(&lst, new);
	}
	return (lst);	
}