/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:25:20 by alvina            #+#    #+#             */
/*   Updated: 2023/04/19 09:35:07 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef enum e_enum
{
	EATING,
	SLEEPING,
	THINKING,
	TAKING_FORK
}	t_enum;

typedef struct s_fork
{
	pthread_mutex_t fork;
	int				status;
}				t_fork;

typedef struct s_everything
{
	int				philosopher;
	int				fork;
	int				ones_dead;
	int				all_meal;
	int				stop_meal;
	pthread_mutex_t	finish;
	pthread_mutex_t	msg;
	pthread_mutex_t	mealing;
	long 			departure;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nb_meal;
}				t_everything;

typedef struct s_philo
{
	int				num;
	pthread_t		thread;
	int				fork_one;
	int				fork_two;
	int				state;
	long			has_eaten;
	int				meals;
	t_everything	*eth;
}				t_philo;

//   --- UTILS ---
long	ft_atoll(const char *nptr);

//    --- INITIALISATION ---
t_everything	*eth_object(int ac, char **av);
t_philo	**tab_philo_init(int nb, t_everything *eth);
t_philo	*philo_init(int num, t_everything *eth);
long	master_of_time(t_philo *philo, int flag);
int	what_the_fork(int num, int lock, t_everything *eth);
t_fork **tab_fork_init(t_everything *eth);

long get_time(void);