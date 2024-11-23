/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:30:15 by wel-safa          #+#    #+#             */
/*   Updated: 2024/11/23 22:04:56 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	escape_the_matrix(t_table *table)
{
	pthread_mutex_lock(&(table->mtx_escape));
	table->escape = 1;
	pthread_mutex_unlock(&(table->mtx_escape));
}

int	_is_escape(t_table *table)
{
	int value;

	pthread_mutex_lock(&(table->mtx_escape));
	value = table->escape;
	pthread_mutex_unlock(&(table->mtx_escape));
	return (value);
}

int	_meals_eaten(t_table *table)
{
	int	value;

	pthread_mutex_lock(&(table->mtx_meals));
	value = table->meals;
	pthread_mutex_unlock(&(table->mtx_meals));
	return (value);
}
