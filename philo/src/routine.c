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

static void	run_routine(t_philosopher *philo)
{
	while (get_status(philo->state))
	{
		print_with_time(philo, "is thinking");
		grab_fork(&philo->fork_r, &philo->fork_r_available);
		print_with_time(philo, "has taken a fork");
		grab_fork(philo->fork_l, philo->fork_l_available);
		print_with_time(philo, "has taken a fork");
		print_with_time(philo, "is eating");
		update_philo_eat_stats(philo);
		scuffed_sleep(philo->state->time_to_eat);
		release_fork(philo->fork_l, philo->fork_l_available);
		release_fork(&philo->fork_r, &philo->fork_r_available);
		print_with_time(philo, "is sleeping");
		scuffed_sleep(philo->state->time_to_sleep);
	}
	return ;
}

void	*philosopher_routine(void *philo_struct)
{
	t_philosopher	*philo;

	philo = (t_philosopher *) philo_struct;
	pthread_mutex_lock(&(philo->state->state_mutex));
	pthread_mutex_unlock(&(philo->state->state_mutex));
	if (!(philo->id % 2))
		scuffed_sleep(1);
	run_routine(philo);
	kill_philosopher_and_end_simulation(philo);
	return (NULL);
}
