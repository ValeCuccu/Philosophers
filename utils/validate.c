/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 12:21:34 by vacuccu           #+#    #+#             */
/*   Updated: 2026/02/10 11:46:38 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	ft_atol(char *s)
{
	int		i;
	long	rest;

	i = 0;
	rest = 0;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '+')
		i++;
	else if (s[i] == '-')
		return (printf("Error: only positive number accepted\n"), -1);
	while (s[i])
	{
		if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
			return (printf("Error: only numeric argument accepted\n"), -1);
		rest = (rest * 10) + (s[i] - '0');
		i++;
	}
	return (rest);
}

int	philosophers_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if ((get_current_time() - philo->last_meal) >= time_to_die)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}
