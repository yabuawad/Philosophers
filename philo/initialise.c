/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabuawad <yabuawad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 17:24:45 by yabuawad          #+#    #+#             */
/*   Updated: 2026/05/18 12:39:08 by yabuawad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_propreties(char **argv, t_prop *prop)
{
	if (!input_check(argv))
		return (0);
	prop->death = 0;
	prop->philos_ate = 0;
	prop->number_of_philosophers = ft_atoi(argv[1]);
	if (prop->number_of_philosophers > 200)
		return (0);
	prop->time_to_die = ft_atoi(argv[2]);
	prop->time_to_eat = ft_atoi(argv[3]);
	prop->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		prop->n_times = ft_atoi(argv[5]);
	else
		prop->n_times = -1;
	return (1);
}

int	init_forks(t_prop *prop, int i)
{
	prop->forks = malloc(sizeof(pthread_mutex_t)
			* prop->number_of_philosophers);
	if (!prop->forks)
		return (0);
	while (i < prop->number_of_philosophers)
	{
		if (pthread_mutex_init(&prop->forks[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&prop->forks[i]);
			return (0);
		}
		i++;
	}
	if (pthread_mutex_init(&prop->meallock, NULL)
		|| pthread_mutex_init(&prop->printlock, NULL)
		|| pthread_mutex_init(&prop->deathlock, NULL))
	{
		i = 0;
		while (i < prop->number_of_philosophers)
			pthread_mutex_destroy(&prop->forks[i++]);
		return (0);
	}
	return (1);
}

void	destroy_mutexes(t_prop *prop)
{
	int	i;

	i = 0;
	while (i < prop->number_of_philosophers)
	{
		pthread_mutex_destroy(&prop->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&prop->printlock);
	pthread_mutex_destroy(&prop->deathlock);
	pthread_mutex_destroy(&prop->meallock);
	free(prop->forks);
}
