/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 18:23:11 by alvina            #+#    #+#             */
/*   Updated: 2023/04/20 16:21:20 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
# define ALL_ALONG 25
# define SINCE_MEAL 26

void    print_msg(t_philo *philo);

int checking(t_philo *philo)
{
    if ((master_of_time(philo, SINCE_MEAL) > philo->eth->time_to_die))
		return (0);
    return (1);
}

void    print_msg(t_philo *philo)
{
    pthread_mutex_lock(&(philo->eth->finish));
	if (philo->eth->ones_dead || philo->eth->stop_meal)
	{
		pthread_mutex_unlock(&(philo->eth->finish));
		return ;
	}
	pthread_mutex_lock(&(philo->eth->msg));
	if (philo->state == EATING)
        printf("%ld %d is eating\n", master_of_time(philo, ALL_ALONG), philo->num);
    else if (philo->state == SLEEPING)
        printf("%ld %d is sleeping\n", master_of_time(philo, ALL_ALONG), philo->num);
    else if (philo->state == THINKING)
        printf("%ld %d is thinking\n", master_of_time(philo, ALL_ALONG), philo->num);
    else
        printf("%ld %d has taken a fork\n", master_of_time(philo, ALL_ALONG), philo->num);
	pthread_mutex_unlock(&(philo->eth->msg));
	pthread_mutex_unlock(&(philo->eth->finish));
}

long get_time(void)
{
    struct timeval time;
    
    gettimeofday(&time, NULL);
    return (((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

int	check_mealing(t_philo **philo)
{
	int				i;
	t_everything	*eth;

	eth = (t_everything *)(*philo)->eth;
	if (eth->nb_meal == -1)
		return (1);
	i = -1;
	while (++i < eth->philosopher)
	{
		pthread_mutex_lock(&(philo[i]->mealing));
		if (philo[i]->meals < eth->nb_meal)
		{
			pthread_mutex_unlock(&(philo[i]->mealing));
			return (1);
		}
		pthread_mutex_unlock(&(philo[i]->mealing));
	}
	pthread_mutex_lock(&eth->finish);
	eth->ones_dead = 1;
	pthread_mutex_unlock(&eth->finish);
	return (0);
	}

void    death_checker(t_philo **philo)
{
    int i;
    t_everything *eth;
    eth = (*philo)->eth;
    while (1)
    {
        i = 0;
		if (!check_mealing(philo))
			return ;
        while (i < eth->philosopher)
        {
            if (!checking(philo[i]))
            {
				pthread_mutex_lock(&eth->finish);
				printf("%ld %d died\n", get_time() - eth->departure, philo[i]->num);
                eth->ones_dead= 1; 
				pthread_mutex_unlock(&eth->finish);
				return ;
            }
            i++;
        }
		usleep(1);
    }
}

long	master_of_time(t_philo *philo, int flag)
{
    long       	time;
	long		res;

	time = get_time();
	if (flag == ALL_ALONG)
        return (time - philo->eth->departure);
    else
	{
		pthread_mutex_lock(&philo->mealing);
		res = time - philo->has_eaten;
		pthread_mutex_unlock(&philo->mealing);
		return (res);
	}
}

static int taking_forks(t_philo *philo)
{
    while (!philo->fork_one || !philo->fork_two)
	{
		if (philo->num % 2 != 0)  // philo numero impair
		{
			if (!philo->fork_one)
			{
				philo->fork_one = what_the_fork(philo->num, 1, philo->eth);
				if (philo->fork_one)
					print_msg(philo);
			}
			if (!philo->fork_two && philo->eth->philosopher != 1)
			{
				if (philo->num == 1)
					philo->fork_two = what_the_fork(philo->eth->philosopher, 1, philo->eth); // philo un
				else
					philo->fork_two = what_the_fork(philo->num - 1, 1, philo->eth);
				if (philo->fork_two)
					print_msg(philo);
			}
		}
		else
		{
			if (!philo->fork_one)
			{
				philo->fork_one = what_the_fork(philo->num - 1, 1, philo->eth);
				if (philo->fork_one)
					print_msg(philo);
			}
			if (!philo->fork_two)
			{
				philo->fork_two = what_the_fork(philo->num, 1, philo->eth);
				if (philo->fork_two)
					print_msg(philo);
			}
		}
		pthread_mutex_lock(&philo->eth->finish);
		if (philo->eth->ones_dead == 1)
			return (0);
		pthread_mutex_unlock(&philo->eth->finish);
	}
	return (1);
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
	long 	start;
	long	now;

	start = get_time();
	while (1)
	{
		now = get_time();
		if (!checking(philo))
            return (0);
		if (now - start >= time)
			return (1);
		usleep(50);
	}
	return (1);
}

static void    eat(t_philo *philo)
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
	if (!ft_usleep(philo->num, philo->eth->time_to_eat, philo))
    {
		leaving_forks(philo);
		return ;
	}
	leaving_forks(philo);
}

static void    sleep_(t_philo *philo)
{
    philo->state = SLEEPING;
	print_msg(philo);
	ft_usleep(philo->num, philo->eth->time_to_sleep, philo);
}

static void    think(t_philo *philo)
{
	philo->state = THINKING;
	print_msg(philo);
	ft_usleep(philo->num, 1, philo);
}

static void	departure(t_philo *philo)
{
	if (philo->num % 2 == 0)
		ft_usleep(philo->num, philo->eth->time_to_eat / 10, philo);
}

void	*life(void *arg)
{
	t_philo			*philo;
	t_everything	*eth;

	philo = (t_philo *)arg;
	eth = philo->eth;
    departure(philo);
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

void	cleaning(t_philo **philo)
{
	t_everything	*eth;
	int				i;
	int				nb;

	i = 0;
	eth = (t_everything *)(*philo)->eth;
	what_the_fork(0, -2, eth);
	nb = eth->philosopher;
	eth_clean(eth);
	while (i < nb)
	{
		pthread_mutex_destroy(&(philo[i]->mealing));
		free(philo[i]);
		i++;
	}
	free(philo);
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
		return (1);
	}
	i = 0;
	eth = eth_object(ac, av);
	if (!eth)
	{
		printf("Error syntax\n");
		return (1);
	}
	if (!eth->nb_meal || !eth->philosopher)
		return (eth_clean(eth), 0);
	philo = tab_philo_init(eth->philosopher, eth);
	what_the_fork(0, -1, eth);
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