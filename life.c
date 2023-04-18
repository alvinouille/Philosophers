/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 18:23:11 by alvina            #+#    #+#             */
/*   Updated: 2023/04/18 14:10:19 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
# define ALL_ALONG 25
# define SINCE_MEAL 26

void    print_msg(long ts, t_philo *philo);

int checking(t_philo *philo)
{
    if (master_of_time(philo, SINCE_MEAL) > philo->eth->time_to_die)
    {
		philo->eth->ones_dead = 1;
		return (0);
    }
    return (1);
}

void    print_msg(long ts, t_philo *philo)
{
    if (philo->eth->ones_dead)
		return ;
	pthread_mutex_lock(&(philo->eth->msg));
	if (philo->state == EATING)
        printf("%ld : philo %d is eating\n", ts, philo->num);
    else if (philo->state == SLEEPING)
        printf("%ld : philo %d is sleeping\n", ts, philo->num);
    else if (philo->state == THINKING)
        printf("%ld : philo %d is thinking\n", ts, philo->num);
    else
        printf("%ld : philo %d has taken a fork\n", ts, philo->num);
	pthread_mutex_unlock(&(philo->eth->msg));
}

long get_time(void)
{
    struct timeval time;
    
    gettimeofday(&time, NULL);
    return (((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}
void    death_checker(t_philo **philo)
{
    int i;
    t_everything *eth;
    eth = (*philo)->eth;
    while (!eth->ones_dead)
    {
        i = 0;
        while (i < eth->philosopher && !eth->ones_dead)
        {
            if (!checking(philo[i]) || eth->stop_meal)
            {
                pthread_mutex_lock(&eth->finish);
				printf("%ld : philo %d died\n", get_time() - eth->departure, philo[i]->num);
                eth->ones_dead = 1;
                pthread_mutex_unlock(&eth->finish);
            }
            i++;
        }
    }
}

long	master_of_time(t_philo *philo, int flag)
{
    long       time;

	time = get_time();
	if (flag == ALL_ALONG)
        return (time - philo->eth->departure);
    else
        return (time - philo->has_eaten);
}

static void taking_forks(t_philo *philo)
{
    while (!philo->fork_one || !philo->fork_two)
	{
		if (philo->num % 2 != 0)  // philo numero impair
		{
			if (!philo->fork_one)
			{
				philo->fork_one = what_the_fork(philo->num, 1, philo->eth);
				if (philo->fork_one)
					print_msg(master_of_time(philo, ALL_ALONG), philo);
			}
			if (!philo->fork_two)
			{
				if (philo->num == 1)
					philo->fork_two = what_the_fork(philo->eth->philosopher, 1, philo->eth); // philo un
				else
					philo->fork_two = what_the_fork(philo->num - 1, 1, philo->eth);
				if (philo->fork_two)
					print_msg(master_of_time(philo, ALL_ALONG), philo);
			}
		}
		else
		{
			if (!philo->fork_one)
			{
				philo->fork_one = what_the_fork(philo->num - 1, 1, philo->eth);
				if (philo->fork_one)
					print_msg(master_of_time(philo, ALL_ALONG), philo);
			}
			if (!philo->fork_two)
			{
				philo->fork_two = what_the_fork(philo->num, 1, philo->eth);
				if (philo->fork_two)
					print_msg(master_of_time(philo, ALL_ALONG), philo);
			}
		}
	}
}

static void leaving_forks(t_philo *philo)
{
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
}

int	ft_usleep(int num, long time, t_philo *philo)
{
	long start;

	start = 0;
	while (start < time)
	{
		usleep(1000);
		start += 1;
		if (!checking(philo))
            return (0);
	}
	return (1);
}
int	mealing(t_philo *philo)
{
	if (!(philo->eth->nb_meal))
		return (1);
	philo->meals++;
	if (philo->meals <= philo->eth->nb_meal)
		philo->eth->all_meal++;
	if (philo->eth->all_meal >= (philo->eth->nb_meal * philo->eth->philosopher))
	{
		printf("all : %d\n, this philo : %d\n", philo->eth->all_meal, philo->eth->nb_meal);
		philo->eth->stop_meal = 1;
		return (0);
	}
	return (1);
}

static void    eat(t_philo *philo)
{
    philo->state = TAKING_FORK;
	taking_forks(philo);
    philo->state = EATING;
	print_msg(master_of_time(philo, ALL_ALONG), philo);
    philo->has_eaten = get_time();
	if (!ft_usleep(philo->num, philo->eth->time_to_eat, philo))
        return ;
	leaving_forks(philo);
	if (!mealing(philo))
		return ;
}

static void    sleep_(t_philo *philo)
{
    philo->state = SLEEPING;
	print_msg(master_of_time(philo, ALL_ALONG), philo);
	if (!ft_usleep(philo->num, philo->eth->time_to_sleep, philo))
		return ;
}

static void    think(t_philo *philo)
{
	philo->state = THINKING;
	print_msg(master_of_time(philo, ALL_ALONG), philo);
	if (!ft_usleep(philo->num, 1, philo))
		return ;
}

static void	departure(t_philo *philo)
{
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

void	*life(void *arg)
{
	t_philo			*philo;
	t_everything	*eth;

	philo = (t_philo *)arg;
	eth = philo->eth;
    departure(philo);
	while (!eth->ones_dead && !eth->stop_meal)
	{
        if (philo->state == THINKING)
            eat(philo);
        else if (philo->state == EATING)
            sleep_(philo);
        else
            think(philo);
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
    eth->departure = get_time();
	while (i < eth->philosopher)
	{
		pthread_create(&(philo[i]->thread), NULL, life, (void *)philo[i]);
		i++;
	}
	i = 0;
    death_checker(philo);
	while (i < eth->philosopher)
    {
        if (pthread_join(philo[i]->thread, NULL) == 0)
			return (0);
		i++;
	}
	pthread_mutex_unlock(&eth->finish);
}