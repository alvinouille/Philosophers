/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniphiphi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:26:07 by alvina            #+#    #+#             */
/*   Updated: 2023/03/08 13:01:35 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void	taking_forks(t_everything *eth, t_list *aot)
// {
// 	struct timeval now;
// 	int fork;
// 	t_philo		*curr;
// 	fork = 0;
// 	curr = aot->philo;
// 	pthread_mutex_lock(&(curr->fork));
// 	gettimeofday(&now, NULL);
// 	printf("%ld : philo %d has taken a fork\n", eth->start - ms_time(now));
// 	curr->forks++;
// 	pthread_mutex_lock(&(aot->next->philo->fork));
// 	gettimeofday(&now, NULL);
// 	printf("%ld : philo %d has taken a fork\n", eth->start - ms_time(now));
//    	curr->forks++;
// 	if (curr->forks == 2)
// 		curr->state = READY_TO_EAT;
// }

static void    eat(t_everything *eth, t_list *aot)
{
	// struct timeval now;
	// int fork;
	t_philo			*curr;

	curr = aot->philo;
	// gettimeofday(&now, NULL);
	// curr->timestamp = eth->start - ms_time(now);
	// printf("%ld : philo %d is eating\n", curr->timestamp);
	// usleep(eth->time_to_eat / 1000);
    // pthread_mutex_unlock(&(curr->fork));
	// curr->forks--;
	// pthread_mutex_unlock(&(aot->next->philo->fork));
	// curr->forks--;
	usleep(eth->time_to_eat);
    printf("eating\n");
    curr->state = READY_TO_SLEEP;
}

static void    sleep_(t_everything *eth, t_list *aot)
{
    t_philo			*curr;

	curr = aot->philo;
    printf("sleeping\n");
    usleep(eth->time_to_sleep);
    curr->state = 2;
}

static void    think(t_everything *eth, t_list *aot)
{
    t_philo			*curr;

	curr = aot->philo;
    printf("thinking\n");
    usleep(2000);
    curr->state = READY_TO_EAT;
}

static long	ms_time(struct timeval time)
{
	return (((time.tv_sec * 1000000) + time.tv_usec) / 1000);
}

static void	departure(t_everything *eth, t_list *aot, int *flag)
{
	t_philo *curr;

	curr = eth->aot->philo;
	if (curr->num % 2 != 0 && *flag == STARTING)
	{
		if (eth->aot->next)
			eat(eth, eth->aot);
		else
			sleep_(eth, eth->aot);
	}
	else
		think(eth, eth->aot);
	*flag = PROCESSING;
	// curr->is_living += curr->timestamp;
}

static void	*life(void *arg)
{
	t_everything	*eth;
	t_philo			*curr;
	int				flag;
	int				action;
	struct timeval	ts;
	struct timeval	now;
	static int counter;
	
	flag = STARTING;
	eth = (t_everything *)arg;
	curr = eth->aot->philo;
	// gettimeofday(&ts, NULL);
	// eth->start = ms_time(ts);
	while (curr->alive)
	{
		if (flag == STARTING)
			departure(eth, eth->aot, &flag);
		else
		{
			// if (curr->state = SLEEPING)
			// 	taking_forks(eth, eth->aot);
			if (curr->state = READY_TO_EAT)
				eat(eth, eth->aot);
			else if (curr->state = READY_TO_SLEEP)
                sleep_(eth, eth->aot);
            else
                think(eth, eth->aot);
		}
		counter++;
		if (counter == 3)
			curr->alive = 0;
	}
}

void    lol(t_everything *eth)
{
    printf("philo numero : %d\n", eth->aot->philo->num);
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
		printf("philo numero : %d\n", eth->aot->philo->num);
        life(eth);
        // lol(eth);
		eth->aot = eth->aot->next;
	}
}