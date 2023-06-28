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

void	join_all_threads(t_philosopher **philo_array)
{
	while (*philo_array)
	{
		pthread_join((*philo_array)->thread, NULL);
		philo_array++;
	}
}

void	free_philosopher_array(t_philosopher **array, bool skip_mutexes)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		if (!skip_mutexes)
		{
			pthread_mutex_destroy(&(array[i]->fork_r));
			pthread_mutex_destroy(&(array[i]->eat_stats_mutex));
		}
		free(array[i]);
		i++;
	}
	free(array);
}
