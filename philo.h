/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:00:23 by alvina            #+#    #+#             */
/*   Updated: 2023/03/10 19:41:43 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef enum e_enum
{
	ABOUT_TO_EAT,
	ABOUT_TO_SLEEP,
	ABOUT_TO_THINK,
	TAKE_A_FORK
}	t_enum;

typedef struct s_fork
{
	pthread_mutex_t fork;
	int				status;
}				t_fork;

typedef struct s_everything
{
	int		philosopher;
	int		fork;
	long	start;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		nb_meal;
}				t_everything;

typedef struct s_philo
{
	int				num;
	pthread_t		thread;
	int				fork_one;
	int				fork_two;
	int				state;
	long			is_living;
	int				meals;
	struct timeval	ts;
	t_everything	*eth;
}				t_philo;

//   --- UTILS ---
long	ft_atoll(const char *nptr);

//    --- INITIALISATION ---
t_everything	*eth_object(int ac, char **av);
t_philo	**tab_philo_init(int nb, t_everything *eth);
t_philo	*philo_init(int num, t_everything *eth);
int	master_of_time(int num, int state, t_philo *philo);
int	what_the_fork(int num, int lock, t_everything *eth);
t_fork **tab_fork_init(t_everything *eth);