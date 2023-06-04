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

t_state	create_state_struct(char **av)
{
	t_state	state;

	memset(&state, 0, sizeof(t_state));
	state.time_to_die = ft_atoi(av[2]);
	state.time_to_eat = ft_atoi(av[3]);
	state.time_to_sleep = ft_atoi(av[4]);
	if (av[5])
	{
		state.has_max_eat_times = true;
		state.should_eat_times = ft_atoi(av[5]);
	}
	state.keep_going = true;
	return (state);
}

static t_philosopher	*setup_philosopher_struct(int i, t_state *state)
{
	t_philosopher	*philosopher;

	philosopher = ft_calloc(1, sizeof(t_philosopher));
	if (!philosopher)
		return (NULL);
	philosopher->id = i;
	philosopher->state = state;
	return (philosopher);
}

bool	setup_philosopher_array(t_philosopher ***philo_array, char **av, \
														t_state *state)
{
	int				count;
	int				i;
	t_philosopher	**philosopher_array;

	count = ft_atoi(av[1]);
	philosopher_array = ft_calloc(count + 1, sizeof(t_philosopher *));
	*philo_array = philosopher_array;
	if (!philosopher_array)
		return (false);
	i = 0;
	while (i < count)
	{
		philosopher_array[i] = setup_philosopher_struct(i + 1, state);
		if (!(philosopher_array[i]))
			return (false);
		i++;
	}
	return (true);
}

static void	clean_up_forks(t_philosopher **philo_array, int limit)
{
	int	i;

	i = 0;
	while (philo_array[i] && i < limit)
	{
		pthread_mutex_destroy(&(philo_array[i]->fork_r));
		i++;
	}
}

bool	distribute_forks(t_philosopher **philo_array)
{
	int	i;

	i = 0;
	while (philo_array[i])
	{
		if (i > 0)
			philo_array[i]->fork_l = &(philo_array[i - 1]->fork_r);
		if (pthread_mutex_init(&(philo_array[i]->fork_r), NULL))
		{
			clean_up_forks(philo_array, i);
			return (false);
		}
		i++;
	}
	philo_array[0]->fork_l = &(philo_array[i - 1]->fork_r);
	return (true);
}
