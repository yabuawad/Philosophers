#include "philo.h"

int init_propreties(char **argv,t_prop *prop)
{
    if(!input_check(argv))
        return 0;
    prop->death = 0;
    prop->number_of_philosophers = ft_atoi(argv[1]);
    if(prop->number_of_philosophers > 200)
        return 0;
    prop->time_to_die = ft_atoi(argv[2]);
    prop->time_to_eat = ft_atoi(argv[3]);
    prop->time_to_sleep = ft_atoi(argv[4]);
    if(argv[5])
        prop->n_times = ft_atoi(argv[5]);
    else
        prop->n_times = -1;
    return 1;
}

int  init_forks(t_prop *prop)
{
    int i = 0;
    prop->forks = malloc(sizeof(pthread_mutex_t) * prop->number_of_philosophers);
    if(!prop->forks)
        return 0;
    while(i < prop->number_of_philosophers)
    {
        pthread_mutex_init(&prop->forks[i],NULL);
        i++;
    }
    pthread_mutex_init(&prop->meallock, NULL);
    pthread_mutex_init(&prop->printlock, NULL);
    pthread_mutex_init(&prop->deathlock, NULL);
    return 1;
}

void destroy_mutexes(t_prop *prop)
{
    int i = 0;
    while(i < prop->number_of_philosophers)
    {
        pthread_mutex_destroy(&prop->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&prop->printlock);
    pthread_mutex_destroy(&prop->deathlock);
    pthread_mutex_destroy(&prop->meallock);
}

void myprint(t_prop *prop,int philo_id,char *message)
{
    long    time;
    long    current_time;
    pthread_mutex_lock(&prop->printlock);
    current_time = getrealtime();
    time = current_time - prop->start_time;
    printf("%ld %i %s\n",time,philo_id,message);
    pthread_mutex_unlock(&prop->printlock);
}