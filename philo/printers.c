/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabuawad <yabuawad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 17:25:12 by yabuawad          #+#    #+#             */
/*   Updated: 2026/05/18 15:29:32 by yabuawad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	getrealtime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_usec / 1000) + tv.tv_sec * 1000);
}

void	zzz(int time_to_sleep, t_prop *prog)
{
	long	initial_time;

	initial_time = getrealtime();
	while ((getrealtime() - initial_time) < time_to_sleep)
	{
		pthread_mutex_lock(&prog->deathlock);
		if (prog->death)
		{
			pthread_mutex_unlock(&prog->deathlock);
			break ;
		}
		pthread_mutex_unlock(&prog->deathlock);
		usleep(600);
	}
}

void	myprint(t_prop *prop, int id, char *msg)
{
	long	time;
	int		dead;

	pthread_mutex_lock(&prop->deathlock);
	dead = prop->death;
	pthread_mutex_unlock(&prop->deathlock);
	if (dead && ft_strncmp(msg, "died", 4) != 0)
		return ;
	pthread_mutex_lock(&prop->printlock);
	time = getrealtime() - prop->start_time;
	printf("%ld %d %s\n", time, id, msg);
	pthread_mutex_unlock(&prop->printlock);
}

void	print_death(t_prop *prop, int id)
{
	pthread_mutex_lock(&prop->deathlock);
	if (prop->death == 0)
	{
		prop->death = 1;
		pthread_mutex_lock(&prop->printlock);
		printf("%ld %d died\n", getrealtime() - prop->start_time, id);
		pthread_mutex_unlock(&prop->printlock);
	}
	pthread_mutex_unlock(&prop->deathlock);
}
