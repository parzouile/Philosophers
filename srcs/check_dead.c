/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dead.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:46:21 by aschmitt          #+#    #+#             */
/*   Updated: 2024/02/21 12:30:32 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_prog(t_program *prog)
{
	int	i;

	i = -1;
	if (prog->forks)
	{
		while (++i < prog->num_of_philos)
			pthread_mutex_destroy(&(prog->forks[i]));
		free(prog->forks);
	}
	if (prog->philos)
		free(prog->philos);
	pthread_mutex_destroy(&prog->write_lock);
	pthread_mutex_destroy(&prog->dead_lock);
	pthread_mutex_destroy(&prog->meal_lock);
}

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
	int	n;

	i = 0;
	n = 0;
	if (philos[0].num_times_to_eat == -1)
		return (0);
	while (i < philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eat >= philos[i].num_times_to_eat)
			n++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (n == philos[0].num_of_philos)
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
	t_philo	*philo;
	int		i;

	philo = (t_philo *)p;
	while (1)
	{
		pthread_mutex_lock(philo[0].start_lock);
		if (*philo[0].start == 1)
		{
			pthread_mutex_unlock(philo[0].start_lock);
			break ;
		}
		pthread_mutex_unlock(philo[0].start_lock);
	}
	
	while (1)
	{
		i = -1;
		while (++i < philo[0].num_of_philos)
		{
			pthread_mutex_lock(philo[i].meal_lock);
			if (get_current_time() - philo[i].last_meal >= philo[i].time_to_die
				&& philo[i].eating == 0)
			{
				pthread_mutex_unlock(philo->meal_lock);
				print(&philo[i], "died");
				break ;
			}
			pthread_mutex_unlock(philo->meal_lock);
		}
		if (i < philo[0].num_of_philos || all_eat(philo))
			break ;
	}
	set_dead(philo);
	return (NULL);
}
