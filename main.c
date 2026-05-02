#include "philo.h"

void *threading(void *arg)
{
    t_philo *p = (t_philo *)arg;
    printf("philo number : %d is running\n",p->philo_id);
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
    prop->time_to_die = ft_atoi(argv[2]);
    prop->time_to_eat = ft_atoi(argv[3]);
    prop->time_to_sleep = ft_atoi(argv[4]);
    return 1;
}
int main(int argc, char **argv)
{
    if(argc != 5)
        return 1;
    t_prop  prop;
    if(!init_propreties(argv,&prop))
        return 1;
    create_philos(&prop);
    free(prop.philo);
}








// void *thread_function(void *arg) // must be void ptr
// {
//     printf("before: %d\n",(int *)arg);
//         (int *)arg++;
//     printf("after: %d\n",(int *)arg);
//     return NULL;
// }

// int main()
// {
//     pthread_t first_thread; //where the threaed ID will be stored
//     pthread_t second_thread;
//     int *i = 0;
//     pthread_create(&first_thread,NULL,thread_function,*i); //first NULL for default thread attributes like stack size//second NULL for the thread_function() argv
//     pthread_create(&second_thread,NULL,thread_function,*i);
//     pthread_join(first_thread,NULL); // because main might finish before the thread
//     pthread_join(second_thread,NULL);
//     return 0;
// }