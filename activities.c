#include "philo.h"


void sleeep(t_philo *philo)
{
    printf("philosopher %i is sleeping\n",philo->philo_id);
    zzz(philo->prop->time_to_sleep);
}

void think(t_philo *philo)
{
    printf("philosopher %i is thinking\n",philo->philo_id);
}

void eat(t_philo *philo)
{
    
}