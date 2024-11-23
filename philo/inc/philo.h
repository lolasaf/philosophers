/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 22:43:16 by wel-safa          #+#    #+#             */
/*   Updated: 2024/11/23 22:20:51 by wel-safa         ###   ########.fr       */
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
# define MUTEX_FAIL "Philosophers: Mutex failed!\n"
# define THREAD_FAIL "Philosophers: Thread failed!\n"

typedef pthread_mutex_t	t_mutex;
typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

struct	s_table
{
	int		num_philos;
	long	start_time;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		max_meals;
	int		meals;
	int		escape;
	t_philo	**philo;
	t_mutex	**forks;
	t_mutex	mtx_print;
	t_mutex	mtx_meals;
	t_mutex mtx_escape;
};

struct s_philo
{
	int			id;
	pthread_t	thread_id;
	t_table	 	*table;
	int			num_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			max_meals;
	int			meals;
	t_mutex		*left_fork;
	t_mutex		*right_fork;
};

// init.c
void	initialize(int ac, char **av, t_table *table);
void	init_input(int ac, char **av, t_table *table);
void	init_table(t_table *table);
void	init_forks(t_table *table);
void	init_philos(t_table *table);

// matrix.c
void	run_matrix(t_table *table);
void	escape_the_matrix(t_table *table);


// utils.c
int		ft_spatoi(const char *nptr);
void	clean_table(t_table *table);
long	timestamp(void);

// mutex.c
int	_is_escape(t_table *table);
int	_meals_eaten(t_table *table);


#endif