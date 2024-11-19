/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 22:43:16 by wel-safa          #+#    #+#             */
/*   Updated: 2024/11/20 00:36:31 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define BAD_INPUT "Philosophers: Incorrect Input - must be 4 or 5 integers\n"
# define MALLOC_FAIL "Philosophers: Malloc failed!\n"

enum	e_error
{
	PARSING_ERROR,
	MALLOC_ERROR
};

typedef pthread_mutex_t	t_mutex;
typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

struct	s_table
{
	int		num_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_servings;
	t_philo	**philo;
	t_mutex	**forks;
	int		meals_eaten;
};

struct s_philo
{
	int	id;
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_servings;
};

void	init_input(int ac, char **av, t_table *table);
void	clean_exit(int error, t_table *table);
int		ft_spatoi(const char *nptr, t_table *table);

#endif