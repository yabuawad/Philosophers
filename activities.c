#include "philo.h"

void sleeep(t_philo *philo)
{
    long    time;
    pthread_mutex_lock(&philo->prop->printlock);
    time = philo->prop->start_time - getrealtime();
    printf("%ld philosopher %i is sleeping\n",time,philo->philo_id);
    pthread_mutex_unlock(&philo->prop->printlock);
    zzz(philo->prop->time_to_sleep);
}

void think(t_philo *philo)
{
    long    time;
    pthread_mutex_lock(&philo->prop->printlock);
    time = philo->prop->start_time - getrealtime();
    printf("%ld philosopher %i is thinking\n",time,philo->philo_id);
    pthread_mutex_unlock(&philo->prop->printlock);
}

void eat(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    myprint(philo->prop,philo->philo_id,"has taken a fork");
    pthread_mutex_lock(philo->right_fork);
    {
        long    time;
        pthread_mutex_lock(&philo->prop->printlock);
        time = philo->prop->start_time - getrealtime();
        printf("%ld philosopher %i has taken a fork\n",philo->philo_id);
        pthread_mutex_unlock(&philo->prop->printlock);
    }
    pthread_mutex_lock(&philo->prop->printlock);
    printf("philosopher %i is eating\n",philo->philo_id);
    pthread_mutex_unlock(&philo->prop->printlock);
    zzz(philo->prop->time_to_eat);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}