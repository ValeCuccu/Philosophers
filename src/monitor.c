/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 12:15:32 by vacuccu           #+#    #+#             */
/*   Updated: 2026/02/11 16:42:35 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_death(t_philo *philo)
{
	int	state;

	pthread_mutex_lock(philo->dead_lock);
	state = *philo->dead;
	pthread_mutex_unlock(philo->dead_lock);
	return (state);
}

int	check_all_ate(t_philo *philos, t_table *table)
{
	int	i;
	int	finished_eating;

	if (philos[0].nb_meals_had_to_eat == -1)
		return (0);
	i = 0;
	finished_eating = 0;
	while (i < table->philos[0].nb_philos)
	{
		pthread_mutex_lock(&table->meal_lock);
		if (philos[i].meals_eaten >= philos[0].nb_meals_had_to_eat)
			finished_eating++;
		pthread_mutex_unlock(&table->meal_lock);
		i++;
	}
	if (finished_eating == table[0].philos->nb_philos)
	{
		pthread_mutex_lock(&table->dead_lock);
		table->dead_flag = 1;
		pthread_mutex_unlock(&table->dead_lock);
		return (1);
	}
	return (0);
}

void	print_status(t_philo *philo, char *str)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_current_time() - philo->start_time;
	if (!check_death(philo))
		printf("%zu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(philo->write_lock);
}

void	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
	{
		if (check_death(philo))
			break ;
		usleep(500);
	}
}

void	monitor_routine(t_philo *philos, t_table *table)
{
	int	i;

	while (1)
	{
		if (check_all_ate(philos, table))
			return ;
		i = 0;
		while (i < table->philos[0].nb_philos)
		{
			if (philosophers_dead(&philos[i], philos[i].time_to_die))
			{
				print_status(&philos[i], "died");
				pthread_mutex_lock(&table->dead_lock);
				table->dead_flag = 1;
				pthread_mutex_unlock(&table->dead_lock);
				return ;
			}
			i++;
		}
		usleep(1000);
	}
}
