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
    if(philo->prop )
    pthread_mutex_lock(philo->left_fork);
    pthread_mutex_lock(philo->right_fork);
    {
        myprint(philo->prop,philo->philo_id,"has taken a fork");
        myprint(philo->prop,philo->philo_id,"has taken a fork");
    }
    myprint(philo->prop,philo->philo_id,"is eating");
    zzz(philo->prop->time_to_eat);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

