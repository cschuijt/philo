/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/30 22:27:53 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/05/30 22:27:53 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_philosopher {
	int				id;
	pthread_t		*thread;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
}	t_philosopher;

#endif
