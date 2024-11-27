/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:30:15 by wel-safa          #+#    #+#             */
/*   Updated: 2024/11/27 19:47:18 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	_meals_eaten(t_table *table)
{
	int	value;

	pthread_mutex_lock(&table->mtx_meals);
	value = table->meals;
	pthread_mutex_unlock(&table->mtx_meals);
	return (value);
}

int	check_max_meals(t_table *table)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&table->mtx_meals);
	while (++i < table->num_philos)
	{
		if (table->philo[i]->meals < table->max_meals)
			return (pthread_mutex_unlock(&table->mtx_meals), 0);
	}
	pthread_mutex_unlock(&table->mtx_meals);
	return (1);
}

long	_last_meal(t_philo *philo)
{
	long	last_meal;

	pthread_mutex_lock(&philo->table->mtx_meals);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&philo->table->mtx_meals);
	return (last_meal);
}

void	m_print_death(t_philo *philo)
{
	escape_the_matrix(philo->table);
	pthread_mutex_lock(&philo->table->mtx_print);
	printf("%ld %d died\n", matrix_time(philo), philo->id);
	pthread_mutex_unlock(&philo->table->mtx_print);
}

/*action: taken from enum variable e_action*/
void	m_print(t_philo *philo, int action)
{
	if (!_is_escape(philo->table))
	{
		pthread_mutex_lock(&philo->table->mtx_print);
		if (action == FORKING)
			printf("%ld %d has taken a fork\n", matrix_time(philo), philo->id);
		if (action == EATING)
			printf("%ld %d is eating\n", matrix_time(philo), philo->id);
		if (action == SLEEPING)
			printf("%ld %d is sleeping\n", matrix_time(philo), philo->id);
		if (action == THINKING)
			printf("%ld %d is thinking\n", matrix_time(philo), philo->id);
		if (action == DYING)
			printf("%ld %d died\n", matrix_time(philo), philo->id);
		pthread_mutex_unlock(&philo->table->mtx_print);
	}
}
