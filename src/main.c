/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 12:35:01 by vacuccu           #+#    #+#             */
/*   Updated: 2026/02/11 15:17:08 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_arg(int ac, char **av, t_philo *p)
{
	if (ac < 5 || ac > 6)
		return (printf("Error: Wrong argument count\n"), 0);
	p->nb_philos = (int)ft_atol(av[1]);
	p->time_to_die = ft_atol(av[2]);
	p->time_to_eat = ft_atol(av[3]);
	p->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		p->nb_meals_had_to_eat = ft_atol(av[5]);
	else
		p->nb_meals_had_to_eat = -1;
	if (p->nb_philos > 200 || p->time_to_die < 0 || p->time_to_eat < 0
		|| p->time_to_sleep < 0 || p->nb_philos <= 0)
		return (printf("Error: Invalid arguments\n"), 0);
	return (1);
}

static void	end_sim(t_table *table, t_philo *philos, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < table->philos[0].nb_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < table->philos[0].nb_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->dead_lock);
	pthread_mutex_destroy(&table->meal_lock);
}

int	main(int ac, char **av)
{
	t_table			table;
	t_philo			philos[200];
	pthread_mutex_t	forks[200];
	int				i;

	if (!check_arg(ac, av, philos))
		return (1);
	init_table(&table, philos);
	init_forks(forks, table.philos->nb_philos);
	init_philos(philos, &table, forks);
	i = 0;
	while (i < table.philos[0].nb_philos)
	{
		if (pthread_create(&philos[i].thread, NULL,
				philo_routine, &philos[i]) != 0)
			return (printf("Error creating thread\n"), 1);
		i++;
	}
	monitor_routine(philos, &table);
	end_sim(&table, philos, forks);
	return (0);
}
