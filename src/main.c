/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 12:35:01 by vacuccu           #+#    #+#             */
/*   Updated: 2026/02/05 14:38:11 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_table				table;
	t_philo				philos[200];
	pthread_mutex_t		forks[200];
	int					nb_philos;

	if (ac < 5 || ac > 6)
		return (1);
	nb_philos = ft_atol(av[1]);
	if (nb_philos > 200)
		nb_philos = 200;
	philos[0].nb_philos = (int)ft_atol(av[1]);
    philos[0].time_to_die = ft_atol(av[2]);
    philos[0].time_to_eat = ft_atol(av[3]);
    philos[0].time_to_sleep = ft_atol(av[4]);
	init_table(&table, philos);
	init_forks(forks, table.philos->nb_philos);
	init_philos(philos, &table, forks);
}
