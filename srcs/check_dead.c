/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dead.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:46:21 by aschmitt          #+#    #+#             */
/*   Updated: 2024/02/12 20:21:09 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	all_eat(t_philo *philos)
{
	int	i;
	int	all_eat;

	i = 0;
	all_eat = 0;
	if (philos[0].num_times_to_eat == -1)
		return (0);
	while (i < philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eat >= philos[0].num_times_to_eat)
			all_eat++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (all_eat == philos[0].num_of_philos)
		return (1);
	return (0);
}

void	set_dead(t_philo *philos)
{
	pthread_mutex_lock(philos[0].dead_lock);
	*philos->dead = 1;
	pthread_mutex_unlock(philos[0].dead_lock);
}

void	*check_dead(void *p)
{
	t_philo *j;
	int		i;

	j = (t_philo *)p;
	while (1)
	{
		i = 0;
		while (i < j[0].num_of_philos)
		{
			pthread_mutex_lock(j->meal_lock);
			if (get_current_time() - j->last_meal >= j->time_to_die && j->eating == 0)
			{
				pthread_mutex_unlock(j->meal_lock);
				break;
			}
			pthread_mutex_unlock(j->meal_lock);
			i++;
		}
		if (i < j[0].num_of_philos || all_eat(j))
		{
			set_dead(j);
			break ;
		}
	}
	return (NULL);
}
