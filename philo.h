/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:46:52 by alvina            #+#    #+#             */
/*   Updated: 2023/04/21 19:24:27 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define ALL_ALONG 25
# define SINCE_MEAL 26

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_enum
{
	EATING,
	SLEEPING,
	THINKING,
	TAKING_FORK
}					t_enum;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				status;
}					t_fork;

typedef struct s_everything
{
	int				philosopher;
	int				fork;
	int				ones_dead;
	int				all_meal;
	int				stop_meal;
	pthread_mutex_t	finish;
	pthread_mutex_t	msg;
	long			departure;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nb_meal;
}					t_everything;

typedef struct s_philo
{
	int				num;
	pthread_t		thread;
	pthread_mutex_t	mealing;
	int				fork_one;
	int				fork_two;
	int				state;
	long			has_eaten;
	int				meals;
	t_everything	*eth;
}					t_philo;

//   --- UTILS ---
long				ft_atoll(const char *nptr);
long				master_of_time(t_philo *philo, int flag);
int					ft_usleep(long time, t_philo *philo);
long				get_time(void);
void				print_msg(t_philo *philo);

//    --- INITIALISATION ---
t_fork				**tab_fork_init(t_everything *eth);
t_fork				*fork_init(void);
t_philo				**tab_philo_init(int nb, t_everything *eth);
t_philo				*philo_init(int num, t_everything *eth);
t_everything		*eth_object(int ac, char **av);
int					arg_checker(long nb);
void				initialising(t_everything **eth, int nb, char *av);

//		--- FORK ---
void				leaving_forks(t_philo *philo);
int					taking_forks(t_philo *philo);
int					what_the_fork(int num, int lock, t_everything *eth);

//		--- CLEAN ---
void				free_tab_fork(t_fork **fork, t_everything *eth);
void				eth_clean(t_everything *eth);
void				cleaning(t_philo **philo);

//		--- CHECKER ---
void				death_checker(t_philo **philo);
int					check_mealing(t_philo **philo);

//		--- LIFE ---
void				*life(void *arg);

#endif