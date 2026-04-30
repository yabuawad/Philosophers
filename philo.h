#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <pthread.h>

typedef struct s_propreties
{
    int     number_of_philosophers;
    int     time_to_die;
    int     time_to_eat;
    int     time_to_sleep;
} t_prop;

typedef struct s_philo
{
    pthread_t   philo_id;
    pthread_t thread;
} t_philo;

# endif