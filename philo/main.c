/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:43:48 by alvina            #+#    #+#             */
/*   Updated: 2023/04/25 18:53:41 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_init(int ac, char **av, t_everything **eth, t_philo ***philo)
{
	if (ac < 5 || ac > 6)
	{
		printf("Error nb of args\n");
		return (0);
	}
	*eth = eth_object(ac, av);
	if (!*eth)
	{
		printf("Error syntax\n");
		return (0);
	}
	if (!(*eth)->nb_meal || !(*eth)->philosopher)
		return (eth_clean(*eth), 0);
	*philo = tab_philo_init((*eth)->philosopher, *eth);
	if (!*philo)
		return (eth_clean(*eth), 0);
	if (!what_the_fork(0, -1, *eth))
		return (eth_clean(*eth), 0);
	return (1);
}

int	main(int ac, char **av)
{
	t_everything	*eth;
	t_philo			**philo;
	int				i;

	i = 0;
	if (!check_init(ac, av, &eth, &philo))
		return (0);
	eth->departure = get_time();
	while (i < eth->philosopher)
	{
		if (pthread_create(&(philo[i]->thread), NULL, life, (void *)philo[i]))
			return (cleaning(philo), 2);
		i++;
	}
	i = 0;
	death_checker(philo);
	while (i < eth->philosopher)
	{
		if (pthread_join(philo[i]->thread, NULL))
			return (cleaning(philo), 2);
		i++;
	}
	cleaning(philo);
}
