/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threader.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabuawad <yabuawad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 17:25:20 by yabuawad          #+#    #+#             */
/*   Updated: 2026/05/14 17:30:20 by yabuawad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	simulation_limit(t_prop *prop)
{
	int	i;

	if (prop->n_times == -1)
		return (0);
	pthread_mutex_lock(&prop->meallock);
	i = 0;
	while (i < prop->number_of_philosophers)
	{
		if (prop->philo[i].eat_times < prop->n_times)
		{
			pthread_mutex_unlock(&prop->meallock);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&prop->meallock);
	return (1);
}

void	*threading(void *arg)
{
	t_philo	*philo;
	int		i;
	int		isdead;

	isdead = 0;
	philo = (t_philo *)arg;
	i = 0;
	if (philo->philo_id % 2 == 0)
		usleep(1000);
	while (!isdead && !simulation_limit(philo->prop))
	{
		pthread_mutex_lock(&philo->prop->deathlock);
		isdead = philo->prop->death;
		pthread_mutex_unlock(&philo->prop->deathlock);
		if (isdead)
			break ;
		eat(philo);
		sleeep(philo);
		think(philo);
	}
	return (NULL);
}

int	check_death(t_prop *prop, int i, int isdead, long last_meal)
{
	prop->philos_ate = 0;
	while (i < prop->number_of_philosophers)
	{
		pthread_mutex_lock(&prop->meallock);
		last_meal = prop->philo[i].last_meal_time;
		pthread_mutex_unlock(&prop->meallock);
		if ((getrealtime() - last_meal) > prop->time_to_die)
		{
			pthread_mutex_lock(&prop->deathlock);
			isdead = prop->death;
			pthread_mutex_unlock(&prop->deathlock);
			if (!isdead)
				print_death(prop, prop->philo[i].philo_id);
			return (0);
		}
		pthread_mutex_lock(&prop->meallock);
		if (prop->philo[i].eat_times == prop->n_times)
			prop->philos_ate++;
		pthread_mutex_unlock(&prop->meallock);
		if (prop->philos_ate == prop->number_of_philosophers)
			return (0);
		i++;
	}
	return (1);
}

void	*controller(void *arg)
{
	t_prop	*prop;

	prop = (t_prop *)arg;
	while (check_death(prop, 0, 0, 0))
		usleep(1000);
	return (NULL);
}
