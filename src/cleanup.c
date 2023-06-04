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

void	free_philosopher_array(t_philosopher **array, bool skip_mutexes)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		if (!skip_mutexes)
			pthread_mutex_destroy(&(array[i]->fork_r));
		free(array[i]);
		i++;
	}
	free(array);
}
