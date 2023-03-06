/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 21:13:59 by alvina            #+#    #+#             */
/*   Updated: 2023/03/06 22:43:07 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_everything	*eth_object(int ac, char **av)
{
	static t_everything *eth;

	if (ac == 0)
		return (eth);
	eth = malloc(sizeof(t_everything));
	eth->philosopher = (int)ft_atoll(av[1]);
	eth->fork = eth->philosopher;
	eth->time_to_die = ft_atoll(av[2]);
	eth->time_to_eat = ft_atoll(av[3]);
	eth->time_to_sleep = ft_atoll(av[4]);
	if (ac == 6)
		eth->nb_meal = (int)ft_atoll(av[5]);
	eth->aot = NULL;
	return (eth);
}

static t_philo	*pair_init(int num)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	new->num = num;
	pthread_mutex_init(&(new->mutex), NULL);
	return (new);
}

static t_list	*aot_init(int nb)
{
	int		i;
	t_list	*lst;
	t_list	*new;
	t_philo	*philo;

	i = 0;
	lst = NULL;
	while (++i < nb + 1)
	{
		philo = pair_init(i);
		new = ft_lstnew((t_philo *)philo);
		ft_lstadd_back(&lst, new);
	}
	return (lst);	
}

int	main(int ac, char **av)
{
	t_everything	*eth;
	t_list			*aot;
	int				i;
	int				nb;

	if (ac < 5 || ac > 6)
	{
		printf("Error nb of args\n");
		exit(EXIT_FAILURE);
	}
	i = -1;
	eth = eth_object(ac, av);
	aot = aot_init(eth->philosopher);
	eth->aot = aot;
	while (++i < eth->philosopher)
	{
		printf("philo numero : %d\n", aot->philo->num);
		aot = aot->next;
	}
}