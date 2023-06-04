/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validations.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/04 13:46:00 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/06/04 13:46:00 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_numericality(char *str)
{
	while (*str)
	{
		if (*str != '+' && *str != '-' && (*str < '0' || *str > '9'))
			return (false);
		str++;
	}
	return (true);
}

bool	run_input_validations(int ac, char **av)
{
	int	i;

	if (ac != 5 && ac != 6)
		return (false);
	i = 1;
	while (av[i])
	{
		if (!check_numericality(av[i]))
		{
			dprintf(2, "'%s': argument is not numeric\n", av[i]);
			return (false);
		}
		if (ft_atoi(av[i]) <= 0)
		{
			dprintf(2, "'%s': argument is not a positive integer\n", av[i]);
			return (false);
		}
		i++;
	}
	return (true);
}
