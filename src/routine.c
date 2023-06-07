/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/04 21:54:30 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/06/04 21:54:30 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

static void	run_left_handed_routine(t_philosopher *philo, bool limited)
{
	while (philo->state->keep_going)
	{
		print_with_time(philo->id, "is thinking");
		pthread_mutex_lock(philo->fork_l);
		print_with_time(philo->id, "has taken a fork");
		pthread_mutex_lock(&(philo->fork_r));
		print_with_time(philo->id, "has taken a fork");
		print_with_time(philo->id, "is eating");
		scuffed_sleep(philo->state->time_to_eat);
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(&(philo->fork_r));
		philo->times_eaten++;
		if (limited && philo->times_eaten >= philo->state->should_eat_times)
			return ;
		print_with_time(philo->id, "is sleeping");
		scuffed_sleep(philo->state->time_to_sleep);
	}
	return ;
}

static void	run_right_handed_routine(t_philosopher *philo, bool limited)
{
	while (philo->state->keep_going)
	{
		print_with_time(philo->id, "is thinking");
		pthread_mutex_lock(&(philo->fork_r));
		print_with_time(philo->id, "has taken a fork");
		pthread_mutex_lock(philo->fork_l);
		print_with_time(philo->id, "has taken a fork");
		print_with_time(philo->id, "is eating");
		scuffed_sleep(philo->state->time_to_eat);
		pthread_mutex_unlock(&(philo->fork_r));
		pthread_mutex_unlock(philo->fork_l);
		philo->times_eaten++;
		if (limited && philo->times_eaten >= philo->state->should_eat_times)
			return ;
		print_with_time(philo->id, "is sleeping");
		scuffed_sleep(philo->state->time_to_sleep);
	}
	return ;
}

void	*philosopher_routine(void *philo_struct)
{
	t_philosopher	*philo;
	int				run_counter;
	int				times_to_run;

	philo = (t_philosopher *) philo_struct;
	run_counter = 0;
	times_to_run = 0;
	if (philo->id == 1)
		run_left_handed_routine(philo, philo->state->has_max_eat_times);
	else
		run_right_handed_routine(philo, philo->state->has_max_eat_times);
	pthread_mutex_lock(&(philo->state->mutex));
	philo->state->keep_going = false;
	pthread_mutex_unlock(&(philo->state->mutex));
	return (NULL);
}
