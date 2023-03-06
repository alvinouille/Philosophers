/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:04:28 by alvina            #+#    #+#             */
/*   Updated: 2023/03/06 21:15:06 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_action
{
    int variable;
    pthread_mutex_t mutex;
}   t_action;

void    variable_init(t_action *action, int *a)
{
    action->variable = *a;
    pthread_mutex_init(&(action->mutex), NULL);
}

void    modify_variable(t_action *action, int *a)
{
    pthread_mutex_lock(&(action->mutex));
    // if ((*a) % 2 != 0)
        usleep(2000);
    printf("%d\n", *a);
    (*a)++;
    (action->variable)++;
    pthread_mutex_unlock(&(action->mutex));
}

void    *routine(void *arg)
{
    t_action *action;
    static int a;
    struct timeval timebefore;
    struct timeval timeafter;
    long int    time_process;
    
    gettimeofday(&timebefore, NULL);
    action = (t_action *)arg;
    printf("in process : a = %d\n", action->variable);
    modify_variable(action, &a);
    gettimeofday(&timeafter, NULL);
    time_process = ((timeafter.tv_sec - timebefore.tv_sec) * 1000000 + (timeafter.tv_usec - timebefore.tv_usec)) / 1000;
    printf("process %d finished : %ld\n", a, time_process);
    return ((void *)action);
}

int main()
{
    pthread_t th[6];
    struct timeval time;
    t_action *action;
    int a = 5;
    int i = 0;
    int *res;
    action = malloc(sizeof(t_action));
    variable_init(action, &a);
    while (i < 6)
    {
        if (pthread_create(&(th[i++]), NULL, routine, (void *)action) != 0)
        {
            printf("Error creating thread\n");
            exit(EXIT_FAILURE);
        }
    }
    i = 0;
    while (i < 6)
    {
        if (pthread_join(th[i++], (void **)&res) != 0)
        {
            printf("Error creating thread\n");
            exit(EXIT_FAILURE);
        }
        printf("out of process : a = %d\n", *res);
    }
    pthread_mutex_destroy(&(action->mutex));
    free(action);
}