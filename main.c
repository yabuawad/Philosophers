#include "philo.h"

void *threading(void *arg)
{
    t_philo *p = (t_philo *)arg;
    while(1)
    {
        sleeep(p);
        think(p);

    }
    // eat(&p);
    // printf("philo number : %d is running\n",p->philo_id);
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

int init_propreties(char **argv,t_prop *prop)
{
    if(!input_check(argv))
        return 0;
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
int main(int argc, char **argv)
{
    if(argc < 5 || argc > 6)
        return 1;
    t_prop  prop;
    if(!init_propreties(argv,&prop))
        return 1;
    create_philos(&prop);
    free(prop.philo);
}







