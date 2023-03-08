/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniphiphi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:26:07 by alvina            #+#    #+#             */
/*   Updated: 2023/03/08 20:36:21 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void    eat(t_philo *philo)
{
	master_of_time(philo->num, ABOUT_TO_EAT, philo);
	usleep(philo->eth->time_to_eat);
    philo->state = ABOUT_TO_SLEEP;
}

static void    sleep_(t_philo *philo)
{
	master_of_time(philo->num, ABOUT_TO_SLEEP, philo);
    usleep(philo->eth->time_to_sleep);
    philo->state = ABOUT_TO_THINK;
}

static void    think(t_philo *philo)
{
	master_of_time(philo->num, ABOUT_TO_THINK, philo);
    usleep(2000);
    philo->state = ABOUT_TO_EAT;
}

static long	ms_time(struct timeval time)
{
	return (((time.tv_sec * 1000000) + time.tv_usec) / 1000);
}

static void	departure(t_philo *philo)
{
	printf("departure\n");
	if (philo->num % 2 != 0)
	{
		if (philo->eth->philosopher != philo->num)
			eat(philo);
		else
			sleep_(philo);
	}
	else
		think(philo);
}

int	master_of_time(int num, int state, t_philo *philo)
{
	static struct timeval	ts;
	struct timeval	now;
	long			time;

	if (!num)
	{
		gettimeofday(&ts, NULL);
		return (1);
	}
	gettimeofday(&now, NULL);
	time = ms_time(now) - ms_time(ts);
	if (time > (philo->eth->time_to_die / 1000))
	{
		printf("%ld : philo %d died\n", time, num);
		return (0);
	}
	else if (state != -1)
	{
		if (state == ABOUT_TO_EAT)
			printf("%ld : philo %d is eating\n", time, num);
		else if (state == ABOUT_TO_SLEEP)
			printf("%ld : philo %d is sleeping\n", time, num);
		else if (state == ABOUT_TO_THINK)
			printf("%ld : philo %d is thinking\n", time, num);
	}
	return (1);
}

static void	*life(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	master_of_time(0, 0, NULL);
	while (philo->is_living != 0)
	{
		if (philo->is_living == -1)
			departure(philo);
		else
		{
			if (philo->state == ABOUT_TO_EAT)
				eat(philo);
			else if (philo->state == ABOUT_TO_SLEEP)
                sleep_(philo);
            else
                think(philo);
		}
		philo->is_living = master_of_time(philo->num, -1, philo);
	}
}

int main(int ac, char **av)
{
	t_everything	*eth;
	t_philo			**philo;
	int				i;
	int				nb;

	if (ac < 5 || ac > 6)
	{
		printf("Error nb of args\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	eth = eth_object(ac, av);
	philo = tab_philo_init(eth->philosopher, eth);
	while (i < eth->philosopher)
	{
		pthread_create(&(philo[i]->thread), NULL, life, (void *)philo[i]);
		i++;
	}
	i = 0;
	while (i < eth->philosopher)
    {
        pthread_join(philo[i]->thread, NULL);
		i++;
	}
}