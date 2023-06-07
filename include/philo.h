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

# define PHILO_SLEEP_INTERVAL 10

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_state {
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	bool			has_max_eat_times;
	int				should_eat_times;
	pthread_mutex_t	mutex;
	bool			keep_going;
	long			start_time;
}	t_state;

typedef struct s_philosopher {
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	fork_r;
	int				times_eaten;
	long			last_eaten;
	t_state			*state;
}	t_philosopher;

//	Validations

bool		run_input_validations(int ac, char **av);

// Setup

t_state		create_state_struct(char **av);
bool		setup_philosopher_array(t_philosopher ***philo_array, char **av, \
														t_state *state);
bool		distribute_forks(t_philosopher **philo_array);

// Routine

void		*philosopher_routine(void *philo_struct);

//	Utilities

int			ft_atoi(char *str);
void		*ft_calloc(size_t num, size_t size);
void		scuffed_sleep(int time);
void		print_with_time(t_philosopher *philo, char *message);
long long	time_in_ms(void);

// Cleanup

void		free_philosopher_array(t_philosopher **array, bool skip_mutexes);

#endif
