#include "philo.h"

void *threading(void *arg)
{
    t_philo *p = (t_philo *)arg;
    while(1)
    {
        sleeep(p);
        think(p);
        eat(p);
        printf("\n");
    }
    return NULL;
}

void create_philos(t_prop *prop)
{
    int     i;
    int     x;

    i = 0;
    x = 0;
    prop->philo = malloc(sizeof(t_philo) * prop->number_of_philosophers);
    if(!prop->philo)
        return;
    while(i < prop->number_of_philosophers)
    {
        prop->philo[i].philo_id = ++x;
        prop->philo[i].prop = prop;
        prop->philo[i].left_fork = &prop->forks[i];
        prop->philo[i].right_fork = &prop->forks[(i + 1) % prop->number_of_philosophers];
        pthread_create(&prop->philo[i].thread,NULL,threading,&prop->philo[i]);
        i++;
    }
    i = 0;
    while(i < prop->number_of_philosophers)
    {
        pthread_join(prop->philo[i].thread,NULL);
        i++;
    }
}


int main(int argc, char **argv)
{
    if(argc < 5 || argc > 6)
        return 1;
    t_prop  prop;
    prop.start_time = getrealtime();
    pthread_mutex_init(&prop.printlock,NULL);
    if(!init_propreties(argv,&prop))
        return 1;
    init_forks(&prop);
    create_philos(&prop);
    freeall(&prop);
}
