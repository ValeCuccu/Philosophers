/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:31:58 by vacuccu           #+#    #+#             */
/*   Updated: 2026/02/11 15:28:55 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_philos(t_philo *philos, t_table *table, pthread_mutex_t *forks)
{
	int	i;
	int	n;

	n = philos[0].nb_philos;
	i = 0;
	while (i < n)
	{
		philos[i].id = i + 1;
		philos[i].nb_philos = n;
		philos[i].start_time = get_current_time();
		philos[i].time_to_die = philos[0].time_to_die;
		philos[i].time_to_sleep = philos[0].time_to_sleep;
		philos[i].time_to_eat = philos[0].time_to_eat;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = get_current_time();
		philos[i].dead = &table->dead_flag;
		philos[i].write_lock = &table->write_lock;
		philos[i].dead_lock = &table->dead_lock;
		philos[i].meal_lock = &table->meal_lock;
		if (i % 2 == 0) // Oppure logica basata sugli indirizzi/indici
		{
		    philos[i].left_fork = &forks[i];
		    philos[i].right_fork = &forks[(i + 1) % n];
		}
		else
		{
		    philos[i].left_fork = &forks[(i + 1) % n];
		    philos[i].right_fork = &forks[i];
		}
		i++;
	}
}

void	init_forks(pthread_mutex_t *forks, int nb_philos)
{
	int	i;

	i = 0;
	while (i < nb_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			printf("Error: Invalid init for forks\n");
			return ;
		}
		i++;
	}
}

void	init_table(t_table *table, t_philo *philos)
{
	table->dead_flag = 0;
	table->philos = philos;
	pthread_mutex_init(&table->write_lock, NULL);
	pthread_mutex_init(&table->dead_lock, NULL);
	pthread_mutex_init(&table->meal_lock, NULL);
}

void	init_thread(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].nb_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, philo_routine,
				&philo[i]) != 0)
		{
			printf("Error init threads\n");
			return ;
		}
		i++;
	}
}
