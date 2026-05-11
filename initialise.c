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
    free(prop->forks);
}

void myprint(t_prop *prop, int id, char *msg)
{
    long time;

    pthread_mutex_lock(&prop->printlock);

    pthread_mutex_lock(&prop->deathlock);
    if (prop->death && ft_strncmp(msg, "died", 4) != 0)
    {
        pthread_mutex_unlock(&prop->deathlock);
        pthread_mutex_unlock(&prop->printlock);
        return;
    }
    pthread_mutex_unlock(&prop->deathlock);
    time = getrealtime() - prop->start_time;
    printf("%ld %d %s\n", time, id, msg);

    pthread_mutex_unlock(&prop->printlock);
}


void print_death(t_prop *prop, int id)
{
    pthread_mutex_lock(&prop->deathlock);
    if (prop->death == 0)
    {
        prop->death = 1;

        pthread_mutex_lock(&prop->printlock);
        printf("%ld %d died\n", getrealtime() - prop->start_time, id);
        pthread_mutex_unlock(&prop->printlock);
    }
    pthread_mutex_unlock(&prop->deathlock);
}