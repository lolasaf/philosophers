/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 21:34:56 by wel-safa          #+#    #+#             */
/*   Updated: 2024/11/26 23:18:01 by wel-safa         ###   ########.fr       */
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
	int	value;

	pthread_mutex_lock(&table->mtx_escape);
	value = table->escape;
	pthread_mutex_unlock(&table->mtx_escape);
	return (value);
}

void	escape_one(t_philo *philo)
{
	m_print(philo, FORKING);
	usleep(philo->time_to_die * 1000);
}
