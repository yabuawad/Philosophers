#include "philo.h"

void create_philos(t_prop prop)
{
    int i = 1;
    while(i < prop.number_of_philosophers + 1)
    {
        t_philo philo;
        pthread_create();
        philo.philo_id = i;
        i++;
    }
}

void init_prop(t_prop prop)
{
    prop.number_of_philosophers = 0;
    prop.time_to_die = 0;
    prop.time_to_eat = 0;
    prop.time_to_sleep = 0;
}
void fill_propreties(char **argv,t_prop prop)
{
    prop.number_of_philosophers = argv[1];
    prop.time_to_die = argv[2];
    prop.time_to_eat = argv[3];
    if(argv[4])
        prop.time_to_sleep = argv[4];
}
int main(int argc, char **argv)
{
    if(argc != 3)
        return 1;
    t_prop prop;
    init_prop(prop);
    fill_propreties(argv,prop);
    create_philos(prop);
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