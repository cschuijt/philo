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

static void	run_left_handed_routine(t_philosopher *philo)
{
	while (philo->state->keep_going)
	{
		print_with_time(philo, "is thinking");
		pthread_mutex_lock(philo->fork_l);
		print_with_time(philo, "has taken a fork");
		pthread_mutex_lock(&(philo->fork_r));
		print_with_time(philo, "has taken a fork");
		print_with_time(philo, "is eating");
		scuffed_sleep(philo->state->time_to_eat);
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(&(philo->fork_r));
		pthread_mutex_lock(&philo->times_eaten_mutex);
		philo->times_eaten++;
		pthread_mutex_unlock(&philo->times_eaten_mutex);
		print_with_time(philo, "is sleeping");
		scuffed_sleep(philo->state->time_to_sleep);
	}
	return ;
}

static void	run_right_handed_routine(t_philosopher *philo)
{
	while (philo->state->keep_going)
	{
		print_with_time(philo, "is thinking");
		pthread_mutex_lock(&(philo->fork_r));
		print_with_time(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_l);
		print_with_time(philo, "has taken a fork");
		print_with_time(philo, "is eating");
		scuffed_sleep(philo->state->time_to_eat);
		pthread_mutex_unlock(&(philo->fork_r));
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_lock(&philo->times_eaten_mutex);
		philo->times_eaten++;
		pthread_mutex_unlock(&philo->times_eaten_mutex);
		print_with_time(philo, "is sleeping");
		scuffed_sleep(philo->state->time_to_sleep);
	}
	return ;
}

void	*philosopher_routine(void *philo_struct)
{
	t_philosopher	*philo;

	philo = (t_philosopher *) philo_struct;
	if (philo->id == 1)
		run_left_handed_routine(philo);
	else
		run_right_handed_routine(philo);
	pthread_mutex_lock(&(philo->state->mutex));
	philo->state->keep_going = false;
	pthread_mutex_unlock(&(philo->state->mutex));
	return (NULL);
}
