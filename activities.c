#include "philo.h"

void sleeep(t_philo *philo)
{
    int isdead;
    pthread_mutex_lock(&philo->prop->deathlock);
    isdead =philo->prop->death;
    pthread_mutex_unlock(&philo->prop->deathlock);
    if(isdead == 1)
        return;
    myprint(philo->prop,philo->philo_id,"is sleeping");
    zzz(philo->prop->time_to_sleep);
}

void think(t_philo *philo)
{
    int isdead;
    pthread_mutex_lock(&philo->prop->deathlock);
    isdead =philo->prop->death;
    pthread_mutex_unlock(&philo->prop->deathlock);
    if(isdead == 1)
        return;
    myprint(philo->prop,philo->philo_id,"is thinking");
    usleep(1000);
}

void set_order(t_philo *philo)
{
    if(philo->left_fork < philo->right_fork)
    {
        philo->first_fork = philo->left_fork;
        philo->second_fork = philo->right_fork;
    } 
    else
    {
        philo->second_fork = philo->left_fork;
        philo->first_fork = philo->right_fork;
    }
}

void eat(t_philo *philo)
{

    if(philo->prop->number_of_philosophers == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        myprint(philo->prop, philo->philo_id, "has taken a fork");
        zzz(philo->prop->time_to_die);
        pthread_mutex_lock(&philo->prop->deathlock);
        if(philo->prop->death == 0)
        {
            myprint(philo->prop, philo->philo_id, "died");
            philo->prop->death = 1;
        }
        pthread_mutex_unlock(&philo->prop->deathlock);
        pthread_mutex_unlock(philo->left_fork);
        return;
    }
    set_order(philo);
    pthread_mutex_lock(philo->first_fork);
    myprint(philo->prop,philo->philo_id,"has taken a fork");
    pthread_mutex_lock(philo->second_fork);
    myprint(philo->prop,philo->philo_id,"has taken a fork");
    pthread_mutex_lock(&philo->prop->meallock);
    philo->last_meal_time = getrealtime();
    pthread_mutex_unlock(&philo->prop->meallock);
    myprint(philo->prop,philo->philo_id,"is eating");
    zzz(philo->prop->time_to_eat);
    pthread_mutex_unlock(philo->first_fork);
    pthread_mutex_unlock(philo->second_fork);
}

