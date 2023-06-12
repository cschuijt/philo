/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printing_and_sleeping.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/07 21:16:54 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/06/07 21:16:54 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

long long	time_in_us(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return (timeval.tv_usec + (timeval.tv_sec * 1000000));
}

long long	time_in_ms(void)
{
	return (time_in_us() / 1000);
}

void	print_with_time(t_philosopher *philo, char *message)
{
	printf("%lld %d %s\n", time_in_ms() - philo->state->start_time, \
				philo->id, message);
}

void	scuffed_sleep(int time_ms)
{
	long long	end_time;
	long long	current_time;

	current_time = time_in_us();
	end_time = current_time + (time_ms * 1000);
	while (current_time < end_time)
	{
		if (current_time + PHILO_SLEEP_INTERVAL < end_time)
			usleep(PHILO_SLEEP_INTERVAL);
		else
		{
			usleep(end_time - current_time);
			return ;
		}
		current_time = time_in_us();
	}
}
