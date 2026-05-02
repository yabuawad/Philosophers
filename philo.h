#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct s_philo
{
    int   philo_id;
    pthread_t   thread;
} t_philo;

typedef struct s_propreties
{
    int     number_of_philosophers;
    int     time_to_die;
    int     time_to_eat;
    int     time_to_sleep;
    pthread_mutex_t     lock;
    t_philo     *philo;
} t_prop;

int	ft_atoi(char *str);
int	ft_isdigit(int c);
int input_check(char **argv);
# endif