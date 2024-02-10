/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:11:02 by aschmitt          #+#    #+#             */
/*   Updated: 2024/02/10 18:07:12 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int ac, char **av)
{
	int	i;

	if (ac < 4 || ac > 5)
		return (1);
	if (check_nbr(av[0]) == -1 || check_nbr(av[0]) > 200)
			return (1);
	i = 0;
	while (++i < ac)
		if (check_nbr(av[i]) == -1)
			return (1);
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	printf("%ld\n", time.tv_sec);
	printf("%ld\n", time.tv_usec);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	main(int ac, char **av)
{
	///pthread_t	t1;
	time_t	start;

	start = get_current_time();
	printf("%ld\n", start);
	if (check_args(ac - 1, av + 1))
		return (write(2, "Error Args\n", 11), 1);

	///pthread_create(&t1, NULL, func1, NULL);

	///pthread_join(t1, NULL);
	return (0);
}