/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:09:38 by vacuccu           #+#    #+#             */
/*   Updated: 2026/02/04 17:18:18 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->nb_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		ft_usleep(philo->time_to_die, philo);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	while (check_death(philo) == 0)
	{
		eat_routine(philo);
		print_status(philo, "is sleeping");
		ft_usleep(philo->time_to_sleep, philo);
		print_status(philo, "is_thinking");
	}
	return (NULL);
}