/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 12:35:01 by vacuccu           #+#    #+#             */
/*   Updated: 2026/02/04 17:05:11 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int main(int ac, char **av)
{
	t_table				table;
	t_philo				philos[200];
	pthread_mutex_t		forks[200];
	int					nb_philos;

	/* check arguments & parsing */
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
	// --- TEST DI DEBUG ---
	printf("Test Inizializzazione:\n");
	printf("Numero filosofi: %d\n", philos[0].nb_philos);
	printf("Indirizzo dead_flag in table: %p\n", (void *)&table.dead_flag);
	printf("Puntatore dead in philo[0]:   %p\n", (void *)philos[0].dead);
	printf("Puntatore dead in philo[199]: %p\n", (void *)philos[199].dead);
	
	// Verifica forchette circolari
	printf("Philo 0 - Left Fork: %p, Right Fork: %p\n", 
	        (void *)philos[0].left_fork, (void *)philos[0].right_fork);
	// Se hai 5 filosofi, l'ultimo è il 4
	int last = philos[0].nb_philos - 1;
	printf("Philo %d - Left Fork: %p, Right Fork: %p\n", 
	        last, (void *)philos[last].left_fork, (void *)philos[last].right_fork);
	// --- FINE TEST ---
}
