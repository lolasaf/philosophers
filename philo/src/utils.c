/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:33:13 by wel-safa          #+#    #+#             */
/*   Updated: 2024/11/26 17:13:35 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_spatoi(const char *nptr)
{
	size_t			i;
	long int		sign;
	long int		res;

	i = 0;
	sign = 1;
	res = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9' && nptr[i])
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	if (nptr[i] || sign < 0 || res > __INT_MAX__)
		return (printf("%s", BAD_INPUT), -1);
	return (res * sign);
}

void	clean_table(t_table *table)
{
	int i;
	
	// free forks
	if (table->forks)
	{
		i = 0;
		while (i < table->num_philos)
			pthread_mutex_destroy(table->forks[i++]);
		i = 0;
		while (i < table->num_philos)
		{
			if (table->forks[i])
				free(table->forks[i]);
			i++;
		}
		free(table->forks);
	}

	// free philos
	if (table->philo)
	{
		i = 0;
		while (i < table->num_philos)
		{
			if (table->philo[i])
				free(table->philo[i]);
			i++;
		}
		free(table->philo);
	}

	// destroy mutexes
	pthread_mutex_destroy(&(table->mtx_escape));
	pthread_mutex_destroy(&(table->mtx_meals));
	pthread_mutex_destroy(&(table->mtx_print));
}

long 	timestamp(t_table *table)
{
	struct timeval	tp;
	long			current_time_ms;

	if (gettimeofday(&tp, NULL) < 0)
		return (printf("%s", "Time Error\n"), clean_table(table), exit(1), 0); 
		// TODO check clean_table here, is it applicable in all cases this function is called
	current_time_ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	return (current_time_ms);
}

long	matrix_time(t_philo *philo)
{
	long	matrix_time_ms;

	matrix_time_ms = timestamp(philo->table) - philo->start_time;
	return (matrix_time_ms);
}
