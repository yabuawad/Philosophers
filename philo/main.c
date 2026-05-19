/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabuawad <yabuawad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 17:24:54 by yabuawad          #+#    #+#             */
/*   Updated: 2026/05/19 11:42:53 by yabuawad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// A mutex only works if ALL accesses to the same data use the SAME mutex

void	join_all(t_prop *prop)
{
	int	i;

	i = 0;
	while (i < prop->number_of_philosophers)
	{
		if(pthread_join(prop->philo[i].thread, NULL))
			return ;
		i++;
	}
	if(pthread_join(prop->controller_id, NULL))
		return;
}

void	create_philos(t_prop *prop)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	prop->philo = malloc(sizeof(t_philo) * prop->number_of_philosophers);
	if (!prop->philo)
		return ;
	while (i < prop->number_of_philosophers)
	{
		prop->philo[i].philo_id = ++x;
		prop->philo[i].prop = prop;
		prop->philo[i].eat_times = 0;
		prop->philo[i].last_meal_time = prop->start_time;
		prop->philo[i].left_fork = &prop->forks[i];
		prop->philo[i].right_fork = &prop->forks[(i + 1)
			% prop->number_of_philosophers];
		if (pthread_create(&prop->philo[i].thread, NULL, threading,
				&prop->philo[i]))
			return ;
		i++;
	}
	if (pthread_create(&prop->controller_id, NULL, controller, prop))
		return ;
	join_all(prop);
}

int	main(int argc, char **argv)
{
	t_prop	prop;

	if (argc < 5 || argc > 6)
		return (1);
	prop.start_time = getrealtime();
	if (!init_propreties(argv, &prop) || !init_forks(&prop,0))
		return (1);
	create_philos(&prop);
	freeall(&prop);
}
