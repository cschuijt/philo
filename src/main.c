/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/30 22:21:55 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/05/30 22:21:55 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	run_simulation(t_philosopher *philo_array, t_state *state)
{
	int	i;

	i = 0;
	state->start_time = time_in_us();
	while (i < state->num_philosophers)
	{
		pthread_create(&(philo_array[i].thread), NULL, \
						philosopher_routine, &(philo_array[i]));
		i++;
	}
}

int	main(int ac, char **av)
{
	t_state			state;
	t_philosopher	*philo_array;

	if (!run_input_validations(ac, av))
		return (1);
	state = create_state_struct(av);
	if (pthread_mutex_init(&state.state_mutex, NULL))
		return (1);
	if (setup_philosopher_array(&philo_array, &state))
	{
		if (distribute_forks(philo_array, &state))
		{
			run_simulation(philo_array, &state);
			monitor_philosophers(philo_array, &state);
			join_all_threads(philo_array, &state);
			free_philosopher_array(philo_array, &state, false);
		}
		else
			free_philosopher_array(philo_array, &state, true);
	}
	pthread_mutex_destroy(&state.state_mutex);
	return (0);
}
