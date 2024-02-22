/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:44:37 by aschmitt          #+#    #+#             */
/*   Updated: 2024/02/21 12:26:18 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_philo(t_program *prog)
{
	pthread_t	check;
	int			i;

	pthread_create(&check, NULL, &check_dead, (void *)prog->philos);
	i = -1;
	while (++i < prog->num_of_philos)
	{
		pthread_create(&(prog->philos[i].thread), NULL, &be_philo,
			(void *)(&prog->philos[i]));
	}
	pthread_mutex_lock(&prog->start_lock);
	prog->start =  get_current_time();
	pthread_mutex_unlock(&prog->start_lock);
	pthread_join(check, NULL);
	i = -1;
	while (++i < prog->num_of_philos)
	{
		pthread_join(prog->philos[i].thread, NULL);
	}
}
