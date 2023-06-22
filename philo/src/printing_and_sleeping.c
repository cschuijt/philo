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

long long	time_in_us(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return (timeval.tv_usec + (timeval.tv_sec * 1000000));
}

long long	time_in_ms(long long delay)
{
	return ((time_in_us() - delay) / 1000);
}

void	print_without_locking(t_philosopher *philo, char *message)
{
	printf("%lld %d %s\n", time_in_ms(philo->state->start_time), \
					philo->id, message);
}

void	print_with_time(t_philosopher *philo, char *message)
{
	pthread_mutex_lock(&(philo->state->state_mutex));
	if (philo->state->keep_going)
	{
		print_without_locking(philo, message);
	}
	pthread_mutex_unlock(&(philo->state->state_mutex));
}

void	scuffed_sleep(int time_ms)
{
	long long	end_time;

	end_time = time_in_us() + (time_ms * 1000);
	while (time_in_us() + PHILO_SLEEP_INTERVAL < end_time)
		usleep(PHILO_SLEEP_INTERVAL);
}
