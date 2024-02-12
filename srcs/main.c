/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:11:02 by aschmitt          #+#    #+#             */
/*   Updated: 2024/02/12 20:28:43 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(int ac, char **av)
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


static t_philo	new_philo(int i, t_program *prog, char **av)
{
	t_philo		p;
	pthread_mutex_t	fork;

	pthread_mutex_init(&fork, NULL);
	p.id = i + 1;
	p.eating = 0;
	p.meals_eat = 0;
	p.last_meal = get_current_time();
	p.time_to_die = check_nbr(av[1]);
	p.time_to_eat = check_nbr(av[2]);
	p.time_to_sleep = check_nbr(av[3]);
	p.start_time = get_current_time();
	p.num_of_philos = prog->num_of_philos;
	if (av[5])
		p.num_times_to_eat = check_nbr(av[5]);
	else
		p.num_times_to_eat = -1;
	p.dead = &prog->dead_flag;
	p.r_fork = &fork;
	if (i != 0)
		p.l_fork = prog->philos[i - 1].r_fork;
	if (i == p.num_of_philos - 1)
		prog->philos[0].l_fork = p.r_fork;
	return (p);
}

static void	init_prog(t_program *prog, char **av)
{
	int	i;

	i = -1;
	prog->dead_flag = 0;
	prog->num_of_philos = check_nbr(av[0]);
	pthread_mutex_init(&prog->dead_lock, NULL);
	pthread_mutex_init(&prog->meal_lock, NULL);
	pthread_mutex_init(&prog->write_lock, NULL);
	prog->philos = (t_philo *)malloc(sizeof(t_philo) * (prog->num_of_philos));
	if (!prog->philos)
		ft_error("Malloc Error\n", prog);
	while (++i < prog->num_of_philos)
	{
		prog->philos[i] = new_philo(i, prog, av);
		prog->philos[i].write_lock = &prog->write_lock;
		prog->philos[i].dead_lock = &prog->dead_lock;
		prog->philos[i].meal_lock = &prog->meal_lock;
	}
}

int	main(int ac, char **av)
{
	t_program	prog;	

	if (check_args(ac - 1, av + 1))
		return (write(2, "Error Args\n", 11), 1);
	init_prog(&prog, av + 1);
	//start_philo(&prog);
	ft_error("caca", &prog);
	return (0);
}
