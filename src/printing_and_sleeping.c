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

long long	time_in_ms(void)
{
	struct timeval	time;
	long long		value;

	gettimeofday(&time, NULL);
	value = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (value);
}

void	print_with_time(t_philosopher *philo, char *message)
{
	printf("%lld %d %s\n", time_in_ms() - philo->state->start_time, \
				philo->id, message);
}

void	scuffed_sleep(int time)
{
	long long	end_time;
	long long	current_time;

	end_time = time_in_ms() + time;
	while (1)
	{
		current_time = time_in_ms();
		if (end_time - current_time <= 0)
			return ;
		else if (end_time - current_time > PHILO_SLEEP_INTERVAL)
		{
			usleep(PHILO_SLEEP_INTERVAL * 1000);
		}
		else
		{
			usleep((end_time - current_time) * 1000);
			return ;
		}
	}
}
