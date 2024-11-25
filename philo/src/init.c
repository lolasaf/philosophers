/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:29:41 by wel-safa          #+#    #+#             */
/*   Updated: 2024/11/25 20:26:26 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// initialize table, philos and forks and mutexes: print, meals, escape
void	initialize(int ac, char **av, t_table *table)
{
	init_input(ac, av, table);
	init_table(table);
}

/*Parses input and initializes corresponding values in table:
num_philos, time_to_die, time_to_eat, time_to_sleep,
and num_servigs if specified, if not it is -1.
It also checks for parsing errors*/
void	init_input(int ac, char **av, t_table *table)
{
	if (ac < 5 || ac > 6)
		return(printf("%s", BAD_INPUT), exit(EXIT_FAILURE));
	table->num_philos = ft_spatoi(av[1]);
	table->time_to_die = ft_spatoi(av[2]);
	table->time_to_eat = ft_spatoi(av[3]);
	table->time_to_sleep = ft_spatoi(av[4]);
	if (table->num_philos < 1 || table->time_to_sleep < 60) // TODO check regarding 60 condition
		return(printf("%s", BAD_INPUT), exit(EXIT_FAILURE));
	if (table->time_to_die < 60 || table->time_to_eat < 60) // TODO check regarding 60 condition
		return(printf("%s", BAD_INPUT), exit(EXIT_FAILURE));
	if (ac == 6)
		table->max_meals = ft_spatoi(av[5]);
	else
		table->max_meals = -1;
}

/*initialize the table*/
void	init_table(t_table *table)
{
	table->escape = 0;
	table->meals = 0;
	
	pthread_mutex_init(&(table->mtx_escape), NULL);
	pthread_mutex_init(&(table->mtx_meals), NULL);
	pthread_mutex_init(&(table->mtx_print), NULL);
	table->philo = NULL;
	table->forks = NULL;
	init_forks(table);
	init_philos(table);
}

/*initialize forks mutexes*/
void	init_forks(t_table *table)
{
	int i = 0;

	table->forks = malloc(sizeof(t_mutex *) * table->num_philos);
	if (!table->forks)
		return(printf("%s", MALLOC_FAIL), clean_table(table), exit(1));
	while (i < table->num_philos)
	{
		table->forks[i] = malloc(sizeof(t_mutex));
		if (!table->forks[i])
			return(printf("%s", MALLOC_FAIL), clean_table(table), exit(1));
		if (pthread_mutex_init(table->forks[i], NULL))
			return(printf("%s", MALLOC_FAIL), clean_table(table), exit(1));
		i++;
	}	
}

/*Initializes philsophers at table based on number of philosophers,
and table values, and sets the right and left mutex fork pointers*/
void	init_philos(t_table *table)
{
	int i = 0;

	table->philo = malloc(sizeof(t_philo *) * table->num_philos);
	if (!table->philo)
		return(printf("%s\n", MALLOC_FAIL), clean_table(table), exit(1));
	while (i < table->num_philos)
	{
		table->philo[i] = malloc(sizeof(t_philo));
		if (!table->philo[i])
			return(printf("%s\n", MALLOC_FAIL), clean_table(table), exit(1));
		table->philo[i]->id = i + 1;
		table->philo[i]->meals = 0;
		table->philo[i]->num_philos = table->num_philos;
		table->philo[i]->max_meals = table->max_meals;
		table->philo[i]->table = table;
		table->philo[i]->time_to_die = table->time_to_die;
		table->philo[i]->time_to_eat = table->time_to_eat;
		table->philo[i]->time_to_sleep = table->time_to_sleep;
		table->philo[i]->left_fork = table->forks[i];
		if (i == 0)
			table->philo[i]->right_fork = table->forks[table->num_philos - 1];
		else
			table->philo[i]->right_fork = table->forks[i - 1];
		i++;
	}
}
