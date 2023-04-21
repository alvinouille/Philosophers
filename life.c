/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 18:23:11 by alvina            #+#    #+#             */
/*   Updated: 2023/04/21 18:48:57 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *philo)
{
	philo->state = TAKING_FORK;
	if (!taking_forks(philo))
	{
		pthread_mutex_unlock(&philo->eth->finish);
		leaving_forks(philo);
		return ;
	}
	philo->state = EATING;
	print_msg(philo);
	pthread_mutex_lock(&(philo->mealing));
	philo->has_eaten = get_time();
	philo->meals++;
	pthread_mutex_unlock(&(philo->mealing));
	if (!ft_usleep(philo->eth->time_to_eat, philo))
	{
		leaving_forks(philo);
		return ;
	}
	leaving_forks(philo);
}

static void	sleep_(t_philo *philo)
{
	philo->state = SLEEPING;
	print_msg(philo);
	ft_usleep(philo->eth->time_to_sleep, philo);
}

static void	think(t_philo *philo)
{
	philo->state = THINKING;
	print_msg(philo);
	ft_usleep(1, philo);
}

void	*life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->num % 2 == 0)
		ft_usleep(philo->eth->time_to_eat / 10, philo);
	while (1)
	{
		if (philo->state == THINKING)
			eat(philo);
		else if (philo->state == EATING)
			sleep_(philo);
		else
			think(philo);
		pthread_mutex_lock(&philo->eth->finish);
		if (philo->eth->ones_dead == 1)
		{
			pthread_mutex_unlock(&philo->eth->finish);
			break ;
		}
		pthread_mutex_unlock(&philo->eth->finish);
	}
	return (NULL);
}
