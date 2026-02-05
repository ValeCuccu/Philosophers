/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:02:25 by vacuccu           #+#    #+#             */
/*   Updated: 2026/02/05 12:06:20 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	{
		if (gettimeofday(&time, NULL) == -1)
			printf("gettimeofday() error\n");
		return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	}
}
