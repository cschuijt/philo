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

#include <philo.h>

bool	get_status(t_state *state)
{
	bool	status;

	pthread_mutex_lock(&(state->mutex));
	status = state->keep_going;
	pthread_mutex_unlock(&(state->mutex));
	return (status);
}

void	shut_down_simulation(t_state *state)
{
	pthread_mutex_lock(&(state->mutex));
	state->keep_going = false;
	pthread_mutex_unlock(&(state->mutex));
}

static bool	get_philo_status(t_philosopher *philo)
{
	bool	status;

	status = true;
	pthread_mutex_lock(&(philo->eat_stats_mutex));
	if (philo->state->has_max_eat_times && \
		philo->times_eaten >= philo->state->should_eat_times)
		status = false;
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
	int	i;

	while (get_status(philo_array[0]->state))
	{
		i = 0;
		while (philo_array[i])
		{
			if (!get_philo_status(philo_array[i]))
			{
				shut_down_simulation(philo_array[i]->state);
				break ;
			}
			i++;
		}
	}
}
