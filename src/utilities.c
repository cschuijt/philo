/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/04 14:32:04 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/06/04 14:32:04 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	print_with_time(int philo_id, char *message)
{
	struct timeval	time;
	int				current_time;

	gettimeofday(&time, NULL);
	current_time = time.tv_usec / 1000;
	printf("%d %d %s\n", current_time, philo_id, message);
}

void	scuffed_sleep(int time)
{
	while (time > 0)
	{
		if (time > 100)
		{
			usleep(100000);
			time -= 100;
		}
		else
		{
			usleep(time * 1000);
			return ;
		}
	}
}

static int	ft_isspace(int c)
{
	return (c == '\t' || c == '\n' || c == '\v' || \
			c == '\f' || c == '\r' || c == ' ');
}

int	ft_atoi(char *str)
{
	long			i;
	unsigned int	minuses;

	i = 0;
	minuses = 0;
	while (*str && ft_isspace(*str))
		str++;
	if (*str && (*str == '+' || *str == '-'))
	{
		if (*str == '-')
			minuses++;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		i = i * 10;
		i = i + (*str - 48);
		str++;
	}
	if (minuses)
		i = i * -1;
	return ((int) i);
}

void	*ft_calloc(size_t num, size_t size)
{
	void	*result;

	result = malloc(num * size);
	if (result)
		memset(result, 0, num * size);
	return (result);
}
