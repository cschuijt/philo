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

void	free_fork_array(pthread_mutex_t **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		pthread_mutex_destroy(array[i]);
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_philosopher_array(t_philosopher **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
