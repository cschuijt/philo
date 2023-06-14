/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reaper.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 19:49:40 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/06/13 19:49:40 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*reaper_routine(void *philo_array)
{
	t_philosopher	**philos;
	int				i;

	philos = (t_philosopher **) philo_array;
	while ((philos[0])->state->keep_going)
	{
		i = 0;
		while (philos[i])
		{
		}
	}
	kill_all_philosophers(philos);
}
