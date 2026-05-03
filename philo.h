#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_propreties t_prop;

typedef struct s_philo
{
    int     philo_id;
    int     isdead;
    int     meals_eaten;
    pthread_t   thread;
    t_prop      *prop;
} t_philo;

typedef struct s_propreties
{
    int     number_of_philosophers;
    int     time_to_die;
    int     time_to_eat;
    int     time_to_sleep;
    int     n_times;
    pthread_mutex_t     lock;
    t_philo     *philo;
} t_prop;

int	ft_atoi(char *str);
int	ft_isdigit(int c);
int input_check(char **argv);
void zzz(int time_to_sleep);
void sleeep(t_philo *philo);
void think(t_philo *philo);
# endif