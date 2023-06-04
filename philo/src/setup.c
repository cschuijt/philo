/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/04 13:45:57 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/06/04 13:45:57 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philosopher	*setup_philosopher_struct(char **av, int i, \
													t_interrupt *interrupt, \
													pthread_mutex_t **forks)
{
	t_philosopher	*philosopher;

	philosopher = ft_calloc(1, sizeof(t_philosopher));
	if (!philosopher)
		return (NULL);
	philosopher->id = i + 1;
	philosopher->fork_l = forks[i];
	philosopher->fork_r = forks[i + 1];
	philosopher->time_to_die = ft_atoi(av[2]);
	philosopher->time_to_eat = ft_atoi(av[3]);
	philosopher->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
	{
		philosopher->has_max_eat_times = true;
		philosopher->should_eat_times = ft_atoi(av[5]);
	}
	philosopher->interrupt = interrupt;
	return (philosopher);
}

bool	setup_philosopher_array(t_philosopher ***philo_array, char **av, \
							t_interrupt *interrupt, pthread_mutex_t **forks)
{
	int				count;
	int				i;
	t_philosopher	**philosopher_array;

	philosopher_array = *philo_array;
	count = ft_atoi(av[1]);
	philosopher_array = ft_calloc(count + 1, sizeof(t_philosopher *));
	if (!philosopher_array)
		return (false);
	i = 0;
	while (i < count)
	{
		philosopher_array[i] = setup_philosopher_struct(av, i + 1, \
														interrupt, forks);
		if (!(philosopher_array[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	setup_fork_array(pthread_mutex_t ***array, char **av)
{
	int				count;
	int				i;

	count = ft_atoi(av[1]);
	*array = ft_calloc(count + 1, sizeof(pthread_mutex_t *));
	if (!(*array))
		return (false);
	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init((*array)[i], NULL))
			return (false);
		i++;
	}
	return (true);
}
