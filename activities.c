#include "philo.h"

void sleeep(t_philo *philo)
{
    myprint(philo->prop,philo->philo_id,"is sleeping");
    zzz(philo->prop->time_to_sleep);
}

void think(t_philo *philo)
{
    myprint(philo->prop,philo->philo_id,"is thinking");
}

void eat(t_philo *philo)
{
    if(philo->left_fork < philo->right_fork)
    {
        philo->first_fork = philo->left_fork;
        philo->second_fork = philo->right_fork;
    } 
    else if(philo->left_fork > philo->right_fork)
    {
        philo->second_fork = philo->left_fork;
        philo->first_fork = philo->right_fork;
    }
    else if(philo->prop->number_of_philosophers == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        myprint(philo->prop,philo->philo_id,"has taken a fork");
        zzz(philo->prop->time_to_die);
        myprint(philo->prop,philo->philo_id,"died");
        freeall(philo->prop);
        exit(1);
    }
    pthread_mutex_lock(philo->first_fork);
    myprint(philo->prop,philo->philo_id,"has taken a fork");
    pthread_mutex_lock(philo->second_fork);
    myprint(philo->prop,philo->philo_id,"has taken a fork");
    myprint(philo->prop,philo->philo_id,"is eating");
    zzz(philo->prop->time_to_eat);
    pthread_mutex_unlock(philo->first_fork);
    pthread_mutex_unlock(philo->second_fork);
}

