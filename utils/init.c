/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:31:58 by vacuccu           #+#    #+#             */
/*   Updated: 2026/02/05 12:08:27 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_table(t_table *table, t_philo *philos)
{
	table->dead_flag = 0;
	table->philos = philos;
	pthread_mutex_init(&table->write_lock, NULL);
	pthread_mutex_init(&table->dead_lock, NULL);
	pthread_mutex_init(&table->meal_lock, NULL);
}

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
		philos[i].time_to_die = philos[0].time_to_die;
		philos[i].time_to_sleep = philos[0].time_to_sleep;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = get_current_time();
		philos[i].dead = &table->dead_flag;
		philos[i].write_lock = &table->write_lock;
		philos[i].dead_lock = &table->dead_lock;
		philos[i].meal_lock = &table->meal_lock;
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % n];
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
