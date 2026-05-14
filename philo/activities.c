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
int check_onephilo(t_philo *philo)
{
    if (philo->prop->number_of_philosophers == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        myprint(philo->prop, philo->philo_id, "has taken a fork");
        zzz(philo->prop->time_to_die);
        pthread_mutex_unlock(philo->left_fork);
        print_death(philo->prop,philo->philo_id);
        return 0;
    }
    return 1;
}

void eat(t_philo *philo)
{
    int isdead;
    pthread_mutex_lock(&philo->prop->deathlock);
    isdead = philo->prop->death;
    pthread_mutex_unlock(&philo->prop->deathlock);
    if (isdead)
        return;
    if (!check_onephilo(philo))
        return;
    set_order(philo);
    pthread_mutex_lock(philo->first_fork);
    myprint(philo->prop, philo->philo_id, "has taken a fork");
    pthread_mutex_lock(philo->second_fork);
    myprint(philo->prop, philo->philo_id, "has taken a fork");
    pthread_mutex_lock(&philo->prop->meallock);
    philo->last_meal_time = getrealtime();
    philo->eat_times++;
    pthread_mutex_unlock(&philo->prop->meallock);
    myprint(philo->prop, philo->philo_id, "is eating");
    pthread_mutex_unlock(philo->first_fork);
    pthread_mutex_unlock(philo->second_fork);
    zzz(philo->prop->time_to_eat);
}
