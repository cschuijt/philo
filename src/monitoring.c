/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/16 21:03:11 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/06/16 21:03:11 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_status(t_state *state)
{
	bool	status;

	pthread_mutex_lock(&(state->state_mutex));
	status = state->keep_going;
	pthread_mutex_unlock(&(state->state_mutex));
	return (status);
}

void	shut_down_simulation(t_state *state)
{
	pthread_mutex_lock(&(state->state_mutex));
	state->keep_going = false;
	pthread_mutex_unlock(&(state->state_mutex));
}

static bool	get_philo_status(t_philosopher *philo, bool *philos_done_eating)
{
	bool	status;

	status = true;
	pthread_mutex_lock(&(philo->eat_stats_mutex));
	if (!(philo->state->has_max_eat_times) || \
		philo->times_eaten < philo->state->should_eat_times)
		*philos_done_eating = false;
	if (time_in_us() >= philo->dies_at)
	{
		print_with_time(philo, "has died");
		status = false;
	}
	pthread_mutex_unlock(&(philo->eat_stats_mutex));
	return (status);
}

void	monitor_philosophers(t_philosopher **philo_array)
{
	int		i;
	bool	philos_done_eating;

	while (get_status(philo_array[0]->state))
	{
		philos_done_eating = true;
		i = 0;
		while (philo_array[i])
		{
			if (!get_philo_status(philo_array[i], &philos_done_eating))
			{
				shut_down_simulation(philo_array[i]->state);
				break ;
			}
			i++;
		}
		if (philos_done_eating)
		{
			shut_down_simulation(philo_array[0]->state);
			break ;
		}
	}
}
