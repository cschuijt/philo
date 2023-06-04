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
# include <string.h>

typedef struct s_interrupt {
	pthread_mutex_t	mutex;
	bool			keep_going;
}	t_interrupt;

typedef struct s_philosopher {
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	bool			has_max_eat_times;
	int				should_eat_times;
	int				times_eaten;
	t_interrupt		*interrupt;
}	t_philosopher;

//	Validations

bool	run_input_validations(int ac, char **av);

// Setup

bool	setup_philosopher_array(t_philosopher ***philo_array, char **av, \
							t_interrupt *interrupt, pthread_mutex_t **forks);
bool	setup_fork_array(pthread_mutex_t ***array_ptr, char **av);

//	Utilities

int		ft_atoi(char *str);
void	*ft_calloc(size_t num, size_t size);

// Cleanup

void	free_fork_array(pthread_mutex_t **array);
void	free_philosopher_array(t_philosopher **array);

#endif
