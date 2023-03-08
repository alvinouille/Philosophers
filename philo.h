/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:00:23 by alvina            #+#    #+#             */
/*   Updated: 2023/03/08 20:28:25 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

# define STARTING 1
# define PROCESSING 0

typedef enum e_enum
{
	ABOUT_TO_EAT,
	ABOUT_TO_SLEEP,
	ABOUT_TO_THINK
}	t_enum;

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
	pthread_mutex_t fork;
	int				forks;
	int				state;
	long			is_living;
	t_everything	*eth;
}				t_philo;

//   --- UTILS ---
long	ft_atoll(const char *nptr);
// t_list	*ft_lstlast(t_list *lst);
// t_list	*ft_lstadd_back(t_list **lst, t_list *new);
// t_list	*ft_lstnew(void *content);
// t_list	*ft_list_at(t_list *begin_list, int nbr);

//    --- INITIALISATION ---
t_everything	*eth_object(int ac, char **av);
t_philo	**tab_philo_init(int nb, t_everything *eth);
t_philo	*philo_init(int num, t_everything *eth);
int	master_of_time(int num, int state, t_philo *philo);