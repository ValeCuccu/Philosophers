/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:11:42 by vacuccu           #+#    #+#             */
/*   Updated: 2026/02/04 17:18:46 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t				thread;
	int						id;
	int						eating;
	int						meals_eaten;
	size_t					last_meal;
	size_t					time_to_die;
	size_t					time_to_sleep;
	size_t					start_time;
	int						nb_philos;
	int						time_to_eat;
	int						*dead;
	pthread_mutex_t			*right_fork;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*write_lock;
	pthread_mutex_t			*dead_lock;
	pthread_mutex_t			*meal_lock;
}	t_philo;

typedef struct s_table
{
	int						dead_flag;
	pthread_mutex_t			dead_lock;
	pthread_mutex_t			meal_lock;
	pthread_mutex_t			write_lock;
	t_philo					*philos;
}	t_table;

/* DEPENDENCIES */

/* UTILS */
long				ft_atol(char *s);

/* INIT */
void				init_table(t_table *table, t_philo *philos);
void				init_philos(t_philo *philos, t_table *table,
						pthread_mutex_t *forks);
void				init_forks(pthread_mutex_t *forks, int nb_philos);

/* TIME */
size_t				get_current_time(void);

/* ROUTINE */
void				*philo_routine(void *arg);

#endif