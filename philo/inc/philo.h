/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 22:43:16 by wel-safa          #+#    #+#             */
/*   Updated: 2024/11/26 23:19:31 by wel-safa         ###   ########.fr       */
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

# define BAD_INPUT "Philosophers: Bad Input - enter 4 or 5 unsigned integers.\n"
# define MALLOC_FAIL "Philosophers: Malloc failed!\n"
# define MUTEX_FAIL "Philosophers: Mutex failed!\n"
# define THREAD_FAIL "Philosophers: Thread failed!\n"

enum e_action
{
	FORKING,
	EATING,
	SLEEPING,
	THINKING,
	DYING
};

typedef pthread_mutex_t	t_mutex;
typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

struct	s_table
{
	int			num_philos;
	long		start_time;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			max_meals;
	int			meals;
	int			escape;
	pthread_t	monitor_id;
	t_philo		**philo;
	t_mutex		**forks;
	t_mutex		mtx_print;
	t_mutex		mtx_meals;
	t_mutex		mtx_escape;
};

struct s_philo
{
	int			id;
	pthread_t	thread_id;
	t_table		*table;
	long		start_time;
	int			num_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			max_meals;
	int			meals;
	long		last_meal_time;
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
void	eat_sleep_think(t_philo *philo);
void	*routine(void *philo_ptr);
void	*monitor_routine(void *table_ptr);
void	eat(t_philo *philo);

// utils.c
int		ft_spatoi(const char *nptr);
void	clean_table(t_table *table);
long	timestamp(t_table *table);
long	matrix_time(t_philo *philo);

// escape.c
void	escape_the_matrix(t_table *table);
int		_is_escape(t_table *table);
void	escape_one(t_philo *philo);

// mutex.c
int		_meals_eaten(t_table *table);
long	_last_meal(t_philo *philo);
void	m_print(t_philo *philo, int action);
int		check_max_meals(t_table *table);

#endif