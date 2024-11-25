/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:03:01 by wel-safa          #+#    #+#             */
/*   Updated: 2024/11/25 23:32:44 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*EATING:
		1- Pick up right fork
			- lock right fork mutex
			- print that I picked up fork
		2- Pick up left fork
			- lock left fork mutex
			- print that I picked up fork
		3- Print I am eating
		4- Update Variables
			- lock mtx_meals
			- philo->last_meal
			- table->meals
			- unlock mtx_meals
			- philo->meals
		5- usleep (time to eat)
		6- Unlock left and right fork

	SLEEPING:
		1- print that I am sleeping
		2- usleep (time_to_sleep * 1000) usleep is in microseconds, ttsleep in ms
	
	THINKING:
		1- print
*/
void	eat_sleep_think(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	m_print(philo, FORKING);
	pthread_mutex_lock(philo->left_fork);
	m_print(philo, FORKING);
	m_print(philo, EATING);
	pthread_mutex_lock(&philo->table->mtx_meals);
	philo->last_meal_time = timestamp(philo->table);
	philo->table->meals++;
	pthread_mutex_unlock(&philo->table->mtx_meals);
	usleep(philo->time_to_sleep * 1000);
	philo->meals++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	m_print(philo, SLEEPING);
	usleep(philo->time_to_sleep * 1000);
	m_print(philo, THINKING);
}

void	*routine(void *philo_ptr)
{
	int	plates;
	int	round;
	int	diff;
	int start_id;
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	while(!(_is_escape(philo->table)) && philo->meals < philo->max_meals)
	{
		plates = philo->num_philos / 2;
		round = _meals_eaten(philo->table) / plates + 1;
		start_id = round % philo->num_philos;
		diff = (philo->id - start_id + philo->num_philos) % philo->num_philos;
		if (((diff % 2) == 0) && (diff < (plates - 1) * 2))
			eat_sleep_think(philo);
		usleep(500);
	}
	escape_the_matrix(philo->table);
	return (NULL);
}

void	*monitor_routine(void *table_ptr)
{
	int		i;

	t_table *table;

	table = (t_table *)table_ptr;
	while(1)
	{
		// loop through philo Ids and check for death!!!
		i = 0;
		while (i < table->num_philos)
		{
			if (timestamp(table) 
					- _last_meal(table->philo[i]) >= table->time_to_die)
			{
				m_print(table->philo[i], DYING);
				escape_the_matrix(table);
				return (NULL);
			}
		}
		usleep(500);
	}
}

void	run_matrix(t_table *table)
{
	int	i;

	i = 0;
	table->start_time = timestamp(table);
	if (pthread_create(&table->monitor_id, NULL, &monitor_routine, table))
		return (printf("%s\n", THREAD_FAIL), escape_the_matrix(table)); //  escape?
	while(i < table->num_philos)
	{
		if (pthread_create(&table->philo[i]->thread_id, NULL, &routine, 
				table->philo[i]))
			return (printf("%s\n", THREAD_FAIL), escape_the_matrix(table)); // escape?
		i++;
	}
	if (pthread_join(table->monitor_id, NULL))
		return(printf("%s\n", THREAD_FAIL), escape_the_matrix(table)); // escape?
	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_join(table->philo[i++]->thread_id, NULL))
			return(printf("%s\n", THREAD_FAIL), escape_the_matrix(table)); // escape?
	}
}
