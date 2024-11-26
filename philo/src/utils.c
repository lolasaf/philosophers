/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:33:13 by wel-safa          #+#    #+#             */
/*   Updated: 2024/11/26 23:21:37 by wel-safa         ###   ########.fr       */
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
	int	i;

	if (table->forks)
	{
		i = -1;
		while (++i < table->num_philos)
			pthread_mutex_destroy(table->forks[i]);
		i = -1;
		while (++i < table->num_philos)
			free(table->forks[i]);
		free(table->forks);
	}
	if (table->philo)
	{
		i = -1;
		while (++i < table->num_philos)
			free(table->philo[i]);
		free(table->philo);
	}
	pthread_mutex_destroy(&(table->mtx_escape));
	pthread_mutex_destroy(&(table->mtx_meals));
	pthread_mutex_destroy(&(table->mtx_print));
}

long	timestamp(t_table *table)
{
	struct timeval	tp;
	long			current_time_ms;

	if (gettimeofday(&tp, NULL) < 0)
		return (printf("%s", "Time Error\n"), 
			escape_the_matrix(table), exit(1), 0); 
	current_time_ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	return (current_time_ms);
}

long	matrix_time(t_philo *philo)
{
	long	matrix_time_ms;

	matrix_time_ms = timestamp(philo->table) - philo->start_time;
	return (matrix_time_ms);
}
