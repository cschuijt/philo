/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/04 13:45:53 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/06/04 13:45:53 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_all_threads(t_philosopher *philo_array, t_state *state)
{
	int	i;

	i = 0;
	while (i < state->num_philosophers)
	{
		pthread_join(philo_array[i].thread, NULL);
		i++;
	}
}

void	free_philosopher_array(t_philosopher *array, t_state *state, \
								bool skip_mutexes)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	if (!skip_mutexes)
	{
		while (i < state->num_philosophers)
		{
			pthread_mutex_destroy(&(array[i].fork_r));
			pthread_mutex_destroy(&(array[i].eat_stats_mutex));
			i++;
		}
	}
	free(array);
}
