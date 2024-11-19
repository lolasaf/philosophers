/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 22:43:27 by wel-safa          #+#    #+#             */
/*   Updated: 2024/11/20 00:32:17 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_exit(int error, t_table *table)
{
	/************What needs to be freed/destroyed***************/
	//
	//
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
}

void	init_table(t_table *table)
{
	table->num_philos = 0;
	table->num_servings = -1;
	table->time_to_die = 0;
	table->time_to_eat = 0;
	table->time_to_sleep = 0;
}

int	main(int ac, char **av)
{
	t_table	table;

	init_table(&table);
	init_input(ac, av, &table);

	return (0);
}
