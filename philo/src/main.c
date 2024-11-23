/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 22:43:27 by wel-safa          #+#    #+#             */
/*   Updated: 2024/11/23 01:13:14 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_exit(int error, t_table *table)
{
	/************What needs to be freed/destroyed***************/
	//
	//
	table->forks = NULL;
	/***********************************************************/
	
	if (error == PARSING_ERROR)
	{
		printf("%s", BAD_INPUT);
		exit(EXIT_FAILURE);
	}
}

void	init_input(int ac, char **av, t_table *table)
{
	if (ac < 5 || ac > 6)
		clean_exit(PARSING_ERROR, table);
	table->num_philos = ft_spatoi(av[1], table);
	table->time_to_die = ft_spatoi(av[2], table);
	table->time_to_eat = ft_spatoi(av[3], table);
	table->time_to_sleep = ft_spatoi(av[4], table);
	if (table->num_philos < 1 || table->time_to_sleep < 60)
		clean_exit(PARSING_ERROR, table);
	if (table->time_to_die < 60 || table->time_to_eat < 60)
		clean_exit(PARSING_ERROR, table);
	if (ac == 6)
		table->num_servings = ft_spatoi(av[5], table);
	else
		table->num_philos = -1;
}

void	*routine()
{
	usleep(2);
}

void	init_philos(t_table *table)
{
	int i = 0;

	table->philo = malloc(sizeof(t_philo *) * table->num_philos);
	if (!table->philo)
		// malloc error
	while (i < table->num_philos)
	{
		table->philo[i]->id = i;
		table->philo[i]->meals_eaten = 0;
		table->philo[i]->num_philos = table->num_philos;
		table->philo[i]->num_servings = table->num_servings;
		table->philo[i]->table = table;
		table->philo[i]->time_to_die = table->time_to_die;
		table->philo[i]->time_to_eat = table->time_to_eat;
		table->philo[i]->time_to_sleep = table->time_to_sleep;
		//table->philo[i]->left_fork = ;
		//table->philo[i]->right_fork = ;
		if (pthread_create(table->philo[i]->thread_id, NULL, &routine, NULL))
			// error
		
		i++;
	}
}

void	init_forks(t_table *table)
{
	int i = 0;

	table->forks = malloc(sizeof(t_mutex *) * table->num_philos);
	if (!table->forks)
		// malloc error
	while (i < table->num_philos)
	{
		table->forks[i] = malloc(sizeof(t_mutex));
		if (!table->forks[i])
			// malloc error
		if (pthread_mutex_init(&(table->forks[i]), NULL))
			// mutex error
		i++;
	}	
}

void	init_table(t_table *table)
{
	init_forks(&table);
	init_philos(&table);
}

int	main(int ac, char **av)
{
	t_table	table;

	init_input(ac, av, &table);
	init_table(&table);

	// initialize philos and forks and mutexes: print, meals, escape

	// destroy mutex
	return (0);
}
