/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:13:58 by aschmitt          #+#    #+#             */
/*   Updated: 2024/02/14 18:29:54 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	not_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (0);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (1);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	print(t_philo *philo, char *s)
{
	pthread_mutex_lock(philo->write_lock);
	if (not_dead(philo))
		printf("%ld %d %s\n", get_current_time() - philo->start_time, philo->id, s);
	pthread_mutex_unlock(philo->write_lock);
}

void	eat(t_philo *philo)
{
	if (philo->num_of_philos == 1)
	{
		pthread_mutex_lock(philo->r_fork);
		print(philo, "has taken a fork");
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->r_fork);
	print(philo, "has taken a fork");
	pthread_mutex_lock(philo->l_fork);
	print(philo, "has taken a fork");
	pthread_mutex_lock(philo->meal_lock);
	print(philo, "is eating");
	philo->eating = 1;
	philo->last_meal = get_current_time();
	philo->meals_eat ++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 0;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	*be_philo(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (not_dead(philo))
	{
		eat(philo);
		print(philo, "is sleeping");
		if (not_dead(philo))
			ft_usleep(philo->time_to_sleep);
		print(philo, "is thinking");
		pthread_mutex_lock(philo->meal_lock);
		pthread_mutex_unlock(philo->meal_lock);
	}
	return (NULL);
}
