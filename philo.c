/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 21:13:59 by alvina            #+#    #+#             */
/*   Updated: 2023/03/07 12:19:04 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    is_eating(t_everything *eth, t_list *aot)
{
	struct timeval now;
	int fork;
	t_philo			*curr;
	
	fork = 0;
	curr = aot->philo;
	pthread_mutex_lock(&(curr->fork));
	gettimeofday(&now, NULL);
	printf("%ld : philo %d has taken a fork\n", eth->start - ms_time(now));
	curr->forks++;
	pthread_mutex_lock(&(aot->next->philo->fork));
	gettimeofday(&now, NULL);
	printf("%ld : philo %d has taken a fork\n", eth->start - ms_time(now));
   	curr->forks++;
	if (curr->forks == 2)
	{
		gettimeofday(&now, NULL);
		curr->timestamp = eth->start - ms_time(now);
		printf("%ld : philo %d is eating\n", curr->timestamp);
		usleep(eth->time_to_eat / 1000);
	}
    pthread_mutex_unlock(&(curr->fork));
	curr->forks--;
	pthread_mutex_unlock(&(aot->next->philo->fork));
	curr->forks--;
}

long	ms_time(struct timeval time)
{
	return (((time.tv_sec * 1000000) + time.tv_usec) / 1000);
}

void	departure(t_everything *eth, t_list *aot, int *state)
{
	t_philo *curr;

	curr = eth->aot;
	if (curr->num % 2 != 0 && *state == STARTING)
	{
		if (eth->aot->next)
			is_eating(eth, eth->aot);
		else
			is_sleeping(eth, eth->aot);
	}
	else
		is_thinking(eth, eth->aot);
	*state = PROCESSING;
	curr->is_living += curr->timestamp;
}

void	*life(void *arg)
{
	t_everything	*eth;
	t_philo			*curr;
	int				state;
	int				action;
	struct timeval	ts;
	struct timeval	now;
	
	state = STARTING;
	eth = (t_everything *)arg;
	curr = eth->aot->philo;
	gettimeofday(&ts, NULL);
	eth->start = ms_time(ts);
	while (curr->alive)
	{
		if (state == STARTING)
			departure(eth, eth->aot, state);
		// taking forks
		if (curr->forks == 2 ) // && est en train de penser avec enum
			is_eating(eth, eth->aot);
		else
	}
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