/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:03:01 by wel-safa          #+#    #+#             */
/*   Updated: 2024/11/23 22:29:05 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_sleep_think(t_philo *philo)
{
	// TODO TODO TODO TODO TODO 
}

void	*routine(t_philo *philo)
{
	int	plates;
	int	round;
	int	diff;
	int start_id;

	while(!(_is_escape(philo->table)) && philo->meals < philo->max_meals)
	{
		plates = philo->num_philos / 2;
		round = _meals_eaten(philo->table) / plates + 1;
		start_id = round % philo->num_philos;
		diff = (philo->id - start_id + philo->num_philos) % philo->num_philos;
		if (((diff % 2) == 0) && (diff < (plates - 1) * 2))
			// eat, sleep, think
		usleep(500);
	}
	escape_the_matrix(philo->table);
	return (NULL);
}

void	run_matrix(t_table *table)
{
	int	i;

	i = 0;
	table->start_time = timestamp();
	while(i < table->num_philos)
	{
		if (pthread_create(&(table->philo[i]->thread_id), NULL, &routine, table->philo[i]))
			return (printf("%s\n", THREAD_FAIL), escape_the_matrix(table));
		i++;
	}
	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_join(table->philo[i++]->thread_id, NULL)) // TODO do we need a return ?
			return(printf("%s\n", THREAD_FAIL), escape_the_matrix(table));
	}
}
