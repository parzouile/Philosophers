/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:11:02 by aschmitt          #+#    #+#             */
/*   Updated: 2024/02/14 18:26:28 by aschmitt         ###   ########.fr       */
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

	p.id = i + 1;
	p.eating = 0;
	p.meals_eat = 0;
	p.last_meal = get_current_time();
	p.time_to_die = check_nbr(av[1]);
	p.time_to_eat = check_nbr(av[2]);
	p.time_to_sleep = check_nbr(av[3]);
	p.start_time = get_current_time();
	p.num_of_philos = prog->num_of_philos;
	if (av[4])
		p.num_times_to_eat = check_nbr(av[4]);
	else
		p.num_times_to_eat = -1;
	p.dead = &prog->dead_flag;
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
	prog->forks = NULL;
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

void	init_forks(pthread_mutex_t **foks, t_program *prog)
{
	int	n;

	n = -1;
	while (++n < prog->num_of_philos)
	{
		pthread_mutex_init(&(*foks)[n], NULL);
	}
	n = -1;
	while (++n < prog->num_of_philos)
	{
		prog->philos[n].r_fork = &(*foks)[n];
		if (n != 0)
			prog->philos[n].l_fork = prog->philos[n - 1].r_fork;
		if (n == prog->num_of_philos - 1)
			prog->philos[0].l_fork = prog->philos[n].r_fork;
	}
}

int	main(int ac, char **av)
{
	t_program	prog;

	if (check_args(ac - 1, av + 1))
		return (write(2, "Error Args\n", 11), 1);
	init_prog(&prog, av + 1);
	prog.forks = malloc(sizeof(pthread_mutex_t) * prog.num_of_philos);
	if (!prog.forks)
		ft_error("Error Malloc\n", &prog);
	init_forks(&prog.forks, &prog);
	start_philo(&prog);
	end_prog(&prog);
	return (0);
}
