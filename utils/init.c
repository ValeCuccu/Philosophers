/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:31:58 by vacuccu           #+#    #+#             */
/*   Updated: 2026/02/11 17:40:25 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	init_philo_vars(t_philo *philo, t_table *table, t_philo *input)
{
	philo->nb_philos = input->nb_philos;
	philo->time_to_die = input->time_to_die;
	philo->time_to_eat = input->time_to_eat;
	philo->time_to_sleep = input->time_to_sleep;
	philo->eating = 0;
	philo->meals_eaten = 0;
	philo->start_time = get_current_time();
	philo->last_meal = get_current_time();
	philo->dead = &table->dead_flag;
	philo->write_lock = &table->write_lock;
	philo->dead_lock = &table->dead_lock;
	philo->meal_lock = &table->meal_lock;
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
		init_philo_vars(&philos[i], table, &philos[0]);
		if (i % 2 == 0)
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
