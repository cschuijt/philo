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
	t_interrupt		interrupt;
	t_philosopher	**philo_array;
	pthread_mutex_t	**forks;

	if (!run_input_validations(ac, av))
		return (1);
	if (pthread_mutex_init(&interrupt.mutex, NULL))
		return (1);
	interrupt.keep_going = true;
	if (!setup_fork_array(&forks, av) && \
		!setup_philosopher_array(&philo_array, av, &interrupt, forks))
	{
		// start_simulation(philo_array);
		printf("ok lol\n");
	}
	free_fork_array(forks);
	free_philosopher_array(philo_array);
	pthread_mutex_destroy(&interrupt.mutex);
	return (0);
}
