/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:00:23 by alvina            #+#    #+#             */
/*   Updated: 2023/03/08 12:35:03 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

# define STARTING 1
# define PROCESSING 0

typedef enum e_action
{
	READY_TO_EAT,
	READY_TO_SLEEP,
	READY_TO_THINK
}	t_action;

typedef struct s_philo
{
	int				num;
	pthread_mutex_t fork;
	int				forks;
	int				state;
	long			timestamp;
	long			is_eating;
	long			is_sleeping;
	long			is_living;
	int				alive;
}				t_philo;

typedef struct s_list
{
	t_philo				*philo;
	struct s_list		*next;	
}				t_list;

typedef struct s_everything
{
	int		philosopher;
	int		fork;
	long	start;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		nb_meal;
	t_list	*aot;
}				t_everything;

//   --- UTILS ---
long	ft_atoll(const char *nptr);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
t_list	*ft_list_at(t_list *begin_list, int nbr);

//    --- INITIALISATION ---
t_everything	*eth_object(int ac, char **av);
t_list	*aot_init(int nb);
t_philo	*philo_init(int num);