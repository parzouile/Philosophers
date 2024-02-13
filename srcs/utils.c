/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:13:58 by aschmitt          #+#    #+#             */
/*   Updated: 2024/02/13 16:30:19 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	check_nbr(const char *str)
{
	long	n;
	size_t	i;

	n = 0;
	i = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		i ++;
	}
	if (str[i] && n == 0)
		return (-1);
	return (n);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

void	ft_error(char *s, t_program *prog)
{
	write(2, s, ft_strlen(s));
	end_prog(prog);
	exit(1);
}

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

void	eat(t_philo *philo)
{
	if (philo->num_of_philos == 1)
	{
		pthread_mutex_lock(philo->r_fork);
		printf("%ld %d has taken a fork\n", get_current_time() - philo->start_time, philo->id);
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->r_fork);
	printf("%ld %d has taken a fork\n", get_current_time() - philo->start_time, philo->id);
	pthread_mutex_lock(philo->l_fork);
	printf("%ld %d has taken a fork\n", get_current_time() - philo->start_time, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	printf("%ld %d is eating\n", get_current_time() - philo->start_time, philo->id);
	philo->eating = 1;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 0;
	philo->last_meal = get_current_time();
	philo->meals_eat ++;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	*be_philo(void *p)
{
	t_philo	*philo;

	
	philo = (t_philo *)p;
	if (philo->id % 2 == 0)
		usleep(2);
	while (not_dead(philo))
	{
		eat(philo);
		if (not_dead(philo))
			printf("%ld %d is sleeping\n", get_current_time() - philo->start_time, philo->id);
		ft_usleep(philo->time_to_sleep);
		if (not_dead(philo))
			printf("%ld %d is thinking\n", get_current_time() - philo->start_time, philo->id);
	}
	return (NULL); //ou p
}
