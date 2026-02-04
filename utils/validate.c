/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 12:21:34 by vacuccu           #+#    #+#             */
/*   Updated: 2026/02/04 15:12:29 by vacuccu          ###   ########.fr       */
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
