/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 21:17:56 by alvina            #+#    #+#             */
/*   Updated: 2023/04/21 18:53:20 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoll(const char *nptr)
{
	int		i;
	long	nb;
	int		neg;

	i = 0;
	nb = 0;
	neg = 1;
	if (!nptr || !nptr[0])
		return (-1);
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - 48);
		i++;
	}
	if (nptr[i])
		return (-1);
	else
		return (nb * neg);
}

void	print_msg(t_philo *philo)
{
	pthread_mutex_lock(&(philo->eth->finish));
	if (philo->eth->ones_dead || philo->eth->stop_meal)
	{
		pthread_mutex_unlock(&(philo->eth->finish));
		return ;
	}
	pthread_mutex_lock(&(philo->eth->msg));
	if (philo->state == EATING)
		printf("%ld %d is eating\n", master_of_time(philo, ALL_ALONG),
			philo->num);
	else if (philo->state == SLEEPING)
		printf("%ld %d is sleeping\n", master_of_time(philo, ALL_ALONG),
			philo->num);
	else if (philo->state == THINKING)
		printf("%ld %d is thinking\n", master_of_time(philo, ALL_ALONG),
			philo->num);
	else
		printf("%ld %d has taken a fork\n", master_of_time(philo, ALL_ALONG),
			philo->num);
	pthread_mutex_unlock(&(philo->eth->msg));
	pthread_mutex_unlock(&(philo->eth->finish));
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

int	ft_usleep(long time, t_philo *philo)
{
	long	start;
	long	now;

	start = get_time();
	while (1)
	{
		now = get_time();
		if (master_of_time(philo, SINCE_MEAL) > philo->eth->time_to_die)
			return (0);
		if (now - start >= time)
			return (1);
		usleep(50);
	}
	return (1);
}

long	master_of_time(t_philo *philo, int flag)
{
	long	time;
	long	res;

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
