/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 18:23:11 by alvina            #+#    #+#             */
/*   Updated: 2023/04/25 19:09:29 by ale-sain         ###   ########.fr       */
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
	pthread_mutex_lock(&(philo->mealing));
	philo->has_eaten = get_time();
	print_msg(philo);
	philo->meals++;
	pthread_mutex_unlock(&(philo->mealing));
	if (!ft_usleep(philo->eth->time_to_eat))
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
	ft_usleep(philo->eth->time_to_sleep);
}

static void	think(t_philo *philo)
{
	philo->state = THINKING;
	print_msg(philo);
	ft_usleep(1);
}

void	*life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->num % 2 == 0)
		ft_usleep(1);
	while (1)
	{
		eat(philo);
		sleep_(philo);
		think(philo);
		pthread_mutex_lock(&philo->eth->finish);
		if (philo->eth->ones_dead == 1)
		{
			pthread_mutex_unlock(&philo->eth->finish);
			break ;
		}
		pthread_mutex_unlock(&philo->eth->finish);
		usleep(((philo->eth->time_to_die - \
		(philo->eth->time_to_eat + philo->eth->time_to_sleep)) / 2));
	}
	return (NULL);
}
