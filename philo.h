/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:00:23 by alvina            #+#    #+#             */
/*   Updated: 2023/03/06 22:39:15 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
	pthread_mutex_t mutex;
	int		        num;
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
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		nb_meal;
	t_list	*aot;
}				t_everything;

long	ft_atoll(const char *nptr);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);