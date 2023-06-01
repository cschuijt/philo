/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/30 22:21:55 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/05/30 22:21:55 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void	*thread_main(void *thread_no)
{
	int	number;

	number = *(int *) thread_no;
	printf("Thread %d: printing stuff\n", number);
	return (0);
}

int	main(int ac, char **av)
{
	int			i;
	int			*j;
	pthread_t	*threads;

	i = 0;
	threads = malloc(sizeof(pthread_t) * 5);
	(void) ac;
	(void) av;
	printf("Main: creating threads.\n");
	while (i < 5)
	{
		j = malloc(sizeof(int));
		*j = i;
		pthread_create(&threads[i], NULL, thread_main, j);
		printf("Main: thread %d created.\n", i);
		i++;
		free(j);
	}
	return (0);
}
