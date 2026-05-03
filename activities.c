#include "philo.h"


void sleeep(t_philo *philo)
{
    printf("philosopher %i is sleeping\n",philo->philo_id);
    zzz(600);
}

void think(t_philo *philo)
{
    printf("philosopher %i is thinking\n",philo->philo_id);
}