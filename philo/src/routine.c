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

static void	update_philo_eat_stats(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->eat_stats_mutex);
	philo->times_eaten++;
	philo->dies_at = time_in_us() + (philo->state->time_to_die * 1000);
	pthread_mutex_unlock(&philo->eat_stats_mutex);
}

static void	run_routine_with_delay(t_philosopher *philo)
{
	pthread_mutex_lock(&(philo->state->state_mutex));
	pthread_mutex_unlock(&(philo->state->state_mutex));
	scuffed_sleep(1);
	while (get_status(philo->state))
	{
		print_with_time(philo, "is thinking");
		pthread_mutex_lock(philo->fork_l);
		print_with_time(philo, "has taken a fork");
		pthread_mutex_lock(&(philo->fork_r));
		print_with_time(philo, "has taken a fork");
		update_philo_eat_stats(philo);
		print_with_time(philo, "is eating");
		scuffed_sleep(philo->state->time_to_eat);
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(&(philo->fork_r));
		print_with_time(philo, "is sleeping");
		scuffed_sleep(philo->state->time_to_sleep);
	}
	return ;
}

static void	run_routine(t_philosopher *philo)
{
	pthread_mutex_lock(&(philo->state->state_mutex));
	pthread_mutex_unlock(&(philo->state->state_mutex));
	while (get_status(philo->state))
	{
		print_with_time(philo, "is thinking");
		pthread_mutex_lock(&(philo->fork_r));
		print_with_time(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_l);
		print_with_time(philo, "has taken a fork");
		print_with_time(philo, "is eating");
		update_philo_eat_stats(philo);
		scuffed_sleep(philo->state->time_to_eat);
		pthread_mutex_unlock(&(philo->fork_r));
		pthread_mutex_unlock(philo->fork_l);
		print_with_time(philo, "is sleeping");
		scuffed_sleep(philo->state->time_to_sleep);
	}
	return ;
}

void	*philosopher_routine(void *philo_struct)
{
	t_philosopher	*philo;

	philo = (t_philosopher *) philo_struct;
	if (philo->id % 2)
		run_routine(philo);
	else
		run_routine_with_delay(philo);
	print_with_time(philo, "has died");
	shut_down_simulation(philo->state);
	return (NULL);
}
