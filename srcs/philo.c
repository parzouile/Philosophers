/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:11:02 by aschmitt          #+#    #+#             */
/*   Updated: 2024/02/12 16:00:02 by aschmitt         ###   ########.fr       */
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
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

t_philo	new_philo(int i, t_program *prog, char **av)
{
	t_philo		p;
	pthread_mutex_t	r_fork;

	pthread_mutex_init(&r_fork, NULL);
	p.id = i + 1;
	p.eating = 0;
	p.meals_eaten = 0;
	p.last_meal = get_current_time();
	p.time_to_die = check_nbr(av[1]);
	p.time_to_eat = check_nbr(av[2]);
	p.time_to_sleep = check_nbr(av[3]);
	p.start_time = get_current_time();
	p.write_lock = &prog->write_lock;
	p.dead_lock = &prog->dead_lock;
	p.meal_lock = &prog->meal_lock;
	p.num_of_philos = prog->num_of_philos;
	if (av[5])
		p.num_times_to_eat = check_nbr(av[5]);
	else
		p.num_times_to_eat = -1;
	p.dead = 0;
	p.r_fork = &r_fork;
	if (i != 0)
		p.l_fork = prog->philos[i - 1].r_fork;
	if (i == p.num_of_philos - 1)
		prog->philos[0].l_fork = p.r_fork;
	return (p);
}

void	init_prog(t_program *prog, char **av)
{
	int	i;

	i = -1;
	prog->dead_flag = 0;
	prog->num_of_philos = check_nbr(av[0]);

	pthread_mutex_init(&prog->dead_lock, NULL);
	pthread_mutex_init(&prog->meal_lock, NULL);
	pthread_mutex_init(&prog->write_lock, NULL);
	prog->philos = (t_philo *)malloc(sizeof(t_philo) * (prog->num_of_philos + 1));
	if (!prog->philos)
		ft_error("Malloc Error\n", prog);
	while (++i < prog->num_of_philos)
	{
		prog->philos[i] = new_philo(i, prog, av);
	}
}

int	main(int ac, char **av)
{
	
	t_program	prog;	

	if (check_args(ac - 1, av + 1))
		return (write(2, "Error Args\n", 11), 1);
	init_prog(&prog, av + 1);
	
	return (0);
}