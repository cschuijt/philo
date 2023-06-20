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

static bool	get_philo_status(t_philosopher philo, t_state *state, \
								bool *philos_done_eating)
{
	bool		status;
	long long	current_time;

	status = true;
	current_time = time_in_us();
	pthread_mutex_lock(&(philo.eat_stats_mutex));
	if (!(state->has_max_eat_times) || \
			philo.times_eaten < state->should_eat_times)
		*philos_done_eating = false;
	if (current_time >= philo.dies_at)
	{
		print_with_time(philo, "has died");
		status = false;
	}
	pthread_mutex_unlock(&(philo.eat_stats_mutex));
	return (status);
}

void	monitor_philosophers(t_philosopher *philo_array, t_state *state)
{
	int		i;
	bool	philos_done_eating;

	while (get_status(state))
	{
		philos_done_eating = true;
		i = 0;
		while (i < state->num_philosophers)
		{
			if (!get_philo_status(philo_array[i], state, &philos_done_eating))
			{
				shut_down_simulation(state);
				break ;
			}
			i++;
		}
		if (philos_done_eating)
		{
			shut_down_simulation(state);
			break ;
		}
	}
}
