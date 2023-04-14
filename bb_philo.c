/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bb_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:26:07 by alvina            #+#    #+#             */
/*   Updated: 2023/04/14 18:30:11 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	ft_usleep(int num, long time, t_philo *philo)
{
	long start;

	start = 0;
	while (start < time)
	{
		usleep(1000);
		start += 1;
		if (!master_of_time(philo->num, -1, philo))
			return (0);
	}
	return (1);
}

int	enough_meal(int nb_meals, int nb_philo, int flag)
{
	static int meals;

	if (flag)
		meals++;
	printf("meals = %d\n", meals);
	if (meals >= (nb_meals * nb_philo))
		return (1);
	return (0);
}

static int    eat(t_philo *philo)
{
	while (!philo->fork_one || !philo->fork_two)
	{
		if (!ft_usleep(philo->num, 1, philo))
			return (0);
		if (philo->num % 2 != 0)  // philo numero impair
		{
			if (!philo->fork_one)
			{
				philo->fork_one = what_the_fork(philo->num, 1, philo->eth);
				if (philo->fork_one)
					master_of_time(philo->num, TAKE_A_FORK, philo);
			}
			if (!philo->fork_two)
			{
				if (philo->num == 1)
					philo->fork_two = what_the_fork(philo->eth->philosopher, 1, philo->eth); // philo un
				else
					philo->fork_two = what_the_fork(philo->num - 1, 1, philo->eth);
				if (philo->fork_two)
					master_of_time(philo->num, TAKE_A_FORK, philo);
			}
		}
		else
		{
			if (!philo->fork_one)
			{
				philo->fork_one = what_the_fork(philo->num - 1, 1, philo->eth);
				if (philo->fork_one)
					master_of_time(philo->num, TAKE_A_FORK, philo);
			}
			if (!philo->fork_two)
			{
				philo->fork_two = what_the_fork(philo->num, 1, philo->eth);
				if (philo->fork_two)
					master_of_time(philo->num, TAKE_A_FORK, philo);
			}
		}
	}
    philo->state = ABOUT_TO_EAT;
	master_of_time(philo->num, ABOUT_TO_EAT, philo);
	if (!ft_usleep(philo->num, philo->eth->time_to_eat, philo))
		return (0);
	// if (philo->eth->nb_meal)
	// {
	// 	philo->meals++;
	// 	if (philo->meals <= philo->eth->nb_meal)
	// 	{
	// 		if (enough_meal(philo->eth->nb_meal, philo->eth->philosopher, 1))
	// 		{
	// 			printf("1\n");
	// 			// exit(0);
	// 			return (0);
	// 		}
	// 	}
	// 	else
	// 	{
	// 		if (enough_meal(philo->eth->nb_meal, philo->eth->philosopher, 0))
	// 		{
	// 			printf("2\n");
	// 			return (0);
	// 		}
	// 			// return (0);
	// 	}
	// }
	if (philo->num == 1)
	{
		if (philo->fork_one)
			philo->fork_one = what_the_fork(philo->eth->philosopher, 0, philo->eth);
		if (philo->fork_two)
			philo->fork_two = what_the_fork(philo->num, 0, philo->eth);
	}
	else
	{
		if (philo->fork_one)
			philo->fork_one = what_the_fork(philo->num - 1, 0, philo->eth);
		if (philo->fork_two)
			philo->fork_two = what_the_fork(philo->num, 0, philo->eth);
	}
    philo->state = ABOUT_TO_SLEEP;
	return (1);
}

static int    sleep_(t_philo *philo)
{
	master_of_time(philo->num, ABOUT_TO_SLEEP, philo);
	if (!ft_usleep(philo->num, philo->eth->time_to_sleep, philo))
		return (0);
    philo->state = ABOUT_TO_THINK;
	return (1);
}

static int    think(t_philo *philo)
{
	master_of_time(philo->num, ABOUT_TO_THINK, philo);
	if (!ft_usleep(philo->num, 1, philo))
		return (0);
	philo->state = TAKE_A_FORK;
	return (1);
}

static long	ms_time(struct timeval time)
{
	return (((time.tv_sec * 1000000) + time.tv_usec) / 1000);
}

static int	departure(t_philo *philo)
{
	if (philo->num % 2 != 0)
	{
		if (philo->eth->philosopher != philo->num)
		{
			if (!eat(philo))
				return (0);
		}
		else
		{
			if (!sleep_(philo))
				return (0);
		}
	}
	else
	{
		if (!think(philo))
			return (0);
	}
	return (1);
}

int	master_of_time(int num, int state, t_philo *philo)
{
	static struct timeval	ts;
	struct timeval	now;
	long			time;

	if (num == 0)
	{
		gettimeofday(&ts, NULL);
		return (1);
	}
	gettimeofday(&now, NULL);
	time = ms_time(now) - ms_time(ts);
	if (time - philo->start > philo->eth->time_to_die)
	{
		pthread_mutex_lock(&(philo->eth->finish));
		printf("%ld : philo %d died\n", time, philo->num);
		return (0);
	}
	else if (state != -1)
	{
		if (state == ABOUT_TO_EAT)
		{
			philo->start = time;
			printf("%ld : philo %d is eating\n", time, num);
		}
		else if (state == ABOUT_TO_SLEEP)
			printf("%ld : philo %d is sleeping\n", time, num);
		else if (state == ABOUT_TO_THINK)
			printf("%ld : philo %d is thinking\n", time, num);
		else if (state == TAKE_A_FORK)
			printf("%ld : philo %d has taken a fork\n", time, num);
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
			philo->is_living = departure(philo);
		else
		{
			if (philo->state == TAKE_A_FORK)
				philo->is_living = eat(philo);
			else if (philo->state == ABOUT_TO_SLEEP)
				philo->is_living = sleep_(philo);
            else
                philo->is_living = think(philo);
		}
	}
	return (NULL);
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
	what_the_fork(0, -1, eth);
	while (i < eth->philosopher)
	{
		pthread_create(&(philo[i]->thread), NULL, life, (void *)philo[i]);
		i++;
	}
	i = 0;
	while (i < eth->philosopher)
    {
        if (pthread_join(philo[i]->thread, NULL) == 0)
		{
			pthread_mutex_unlock(&(philo[i]->eth->finish));
			return (0);
		}
		i++;
	}
}