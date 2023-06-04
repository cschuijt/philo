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

int	main(int ac, char **av)
{
	t_state			state;
	t_philosopher	**philo_array;

	if (!run_input_validations(ac, av))
		return (1);
	state = create_state_struct(av);
	if (pthread_mutex_init(&state.mutex, NULL))
		return (1);
	if (setup_philosopher_array(&philo_array, av, &state))
	{
		if (distribute_forks(philo_array))
		{
			// start_simulation(philo_array);
			free_philosopher_array(philo_array, false);
		}
		else
			free_philosopher_array(philo_array, true);
	}
	pthread_mutex_destroy(&state.mutex);
	return (0);
}
