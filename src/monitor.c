/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 12:15:32 by vacuccu           #+#    #+#             */
/*   Updated: 2026/02/05 17:07:09 by vacuccu          ###   ########.fr       */
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
		if ()
	}
}

void	print_status(t_philo *philo, char *str)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_current_time() - philo->start_time;
	/* se non muore nessuno stampo altrimenti nada */
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
