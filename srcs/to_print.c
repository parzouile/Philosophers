/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:09:42 by aschmitt          #+#    #+#             */
/*   Updated: 2024/02/28 13:07:10 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putchar(char c)
{
	(write(1, &c, 1));
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

void	ft_putnbr(size_t nb)
{
	if (nb >= 10)
		(ft_putnbr(nb / 10), ft_putnbr(nb % 10));
	else
		(ft_putchar(nb + '0'));
}

void	print(t_philo *philo, char *s)
{
	pthread_mutex_lock(philo->write_lock);
	if (not_dead(philo))
		printf("%ld %d %s\n", get_current_time() - philo->start_time, philo->id, s);
	pthread_mutex_unlock(philo->write_lock);
}
