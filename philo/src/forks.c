/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   forks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/27 23:27:04 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/06/27 23:27:04 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_fork(pthread_mutex_t *mutex, bool *fork_available)
{
	while (1)
	{
		pthread_mutex_lock(mutex);
		if (*fork_available)
		{
			*fork_available = false;
			break ;
		}
		pthread_mutex_unlock(mutex);
		usleep(PHILO_FORK_CHECK_INTERVAL);
	}
	pthread_mutex_unlock(mutex);
}

void	release_fork(pthread_mutex_t *mutex, bool *fork_available)
{
	pthread_mutex_lock(mutex);
	*fork_available = true;
	pthread_mutex_unlock(mutex);
}
