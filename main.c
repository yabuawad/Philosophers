#include "philo.h"
//A mutex only works if ALL accesses to the same data use the SAME mutex
void    *threading(void *arg)
{
    t_philo *philo;
    int i;
    int isdead = 0;

    philo = (t_philo *)arg;
    i = 0;
    // pthread_mutex_lock(&philo->prop->meallock);
    // philo->last_meal_time = getrealtime();
    // pthread_mutex_unlock(&philo->prop->meallock);
    while (!isdead)
    {
        pthread_mutex_lock(&philo->prop->deathlock);
        isdead =philo->prop->death; 
        pthread_mutex_unlock(&philo->prop->deathlock);
        if(isdead)
            break;
        eat(philo);
        sleeep(philo);
        think(philo);
        // printf("\n");
    }
    return NULL;
}


int    check_death(t_prop *prop)
{
    int     i;
    int     isdead;
    long    last_meal;    

    i = 0;
    while(i < prop->number_of_philosophers)
    {
        pthread_mutex_lock(&prop->meallock);
        last_meal = prop->philo[i].last_meal_time;
        pthread_mutex_unlock(&prop->meallock);
        if((getrealtime() - last_meal) > prop->time_to_die)
        {
            pthread_mutex_lock(&prop->deathlock);
            isdead = prop->death;
            pthread_mutex_unlock(&prop->deathlock);
            if(!isdead)
            {
                pthread_mutex_lock(&prop->deathlock);
                prop->death= 1;
                pthread_mutex_unlock(&prop->deathlock);
                myprint(prop,prop->philo[i].philo_id,"died");
            }
            return 0;
        }
        i++;
    }
    return 1;
}

void    *controller(void *arg)
{
    t_prop  *prop;

    prop = (t_prop *)arg;
    while(1)
    {
        if(!check_death(prop))
            return NULL;
        usleep(1000);
        pthread_mutex_lock(&prop->deathlock);
        if(prop->death == 1)
        {
            pthread_mutex_unlock(&prop->deathlock);
            return NULL;
        }
        pthread_mutex_unlock(&prop->deathlock);
    }
    return NULL;
}

void join_all(t_prop *prop)
{
    int    i;
    i = 0;
    while(i < prop->number_of_philosophers)
    {
        pthread_join(prop->philo[i].thread,NULL);
        i++;
    }
    pthread_join(prop->controller_id,NULL);
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
        prop->philo[i].last_meal_time = prop->start_time;
        prop->philo[i].left_fork = &prop->forks[i];
        prop->philo[i].right_fork = &prop->forks[(i + 1) % prop->number_of_philosophers];
        pthread_create(&prop->philo[i].thread,NULL,threading,&prop->philo[i]);
        i++;
    }
    pthread_create(&prop->controller_id,NULL,controller,prop);
    join_all(prop);
}


int main(int argc, char **argv)
{
    if(argc < 5 || argc > 6)
        return 1;
    t_prop  prop;
    prop.start_time = getrealtime();
    pthread_mutex_init(&prop.printlock,NULL);
    if(!init_propreties(argv,&prop) || !init_forks(&prop))
        return 1;
    create_philos(&prop);
    freeall(&prop);
}
