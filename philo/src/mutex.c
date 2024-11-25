/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:30:15 by wel-safa          #+#    #+#             */
/*   Updated: 2024/11/25 23:33:52 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	escape_the_matrix(t_table *table)
{
	pthread_mutex_lock(&table->mtx_escape);
	table->escape = 1;
	pthread_mutex_unlock(&table->mtx_escape);
}

int	_is_escape(t_table *table)
{
	int value;

	pthread_mutex_lock(&table->mtx_escape);
	value = table->escape;
	pthread_mutex_unlock(&table->mtx_escape);
	return (value);
}

int	_meals_eaten(t_table *table)
{
	int	value;

	pthread_mutex_lock(&table->mtx_meals);
	value = table->meals;
	pthread_mutex_unlock(&table->mtx_meals);
	return (value);
}

long	_last_meal(t_philo *philo)
{
	long last_meal;

	pthread_mutex_lock(&philo->table->mtx_meals);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&philo->table->mtx_meals);
	return (last_meal);
}

/*action: taken from enum variable e_action*/
void	m_print(t_philo *philo, int action)
{
	if (!_is_escape(philo->table))
	{
		pthread_mutex_lock(&philo->table->mtx_print);
		if (action == FORKING)
			printf("%ld %d has taken a fork", matrix_time(philo), philo->id);
		if (action == EATING)
			printf("%ld %d is eating", matrix_time(philo), philo->id);
		if (action == SLEEPING)
			printf("%ld %d is sleeping", matrix_time(philo), philo->id);
		if (action == THINKING)
			printf("%ld %d is thinking", matrix_time(philo), philo->id);
		if (action == DYING)
			printf("%ld %d died", matrix_time(philo), philo->id);
		pthread_mutex_unlock(&philo->table->mtx_print);
	}
}
