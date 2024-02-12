/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:13:58 by aschmitt          #+#    #+#             */
/*   Updated: 2024/02/12 16:04:55 by aschmitt         ###   ########.fr       */
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
	(void)prog;
	exit(1);
}

int	not_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	be_philo(void *p)
{
	t_philo	*philo;

	philo = (t_philo*)p;
	
	while (not_dead(philo))
	{
		///eat
		///sleep
		///drink
	}
}
