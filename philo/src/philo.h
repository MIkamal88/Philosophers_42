/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:22:23 by m_kamal           #+#    #+#             */
/*   Updated: 2023/10/15 17:22:23 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define INT_MAX 2147483647

# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define FORK "has taken a fork"
# define DIED "died"

//Colors
# define RESET "\e[0m"
# define GREEN "\e[0;32m"
# define G_BLUE "\e[0;38;5;24m"
# define B_BLUE "\e[1;34m"
# define G_CYAN "\e[0;38;5;44m"
# define RED "\033[31;1m"
# define YELLOW "\033[1;33m"
# define WHITE "\033[1;37m"

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_args
{
	long	t0;
	int		philo_n;
	long	die_t;
	long	eat_t;
	long	sleep_t;
	int		meals_n;
}	t_args;

enum e_fork
{
	RIGHT,
	LEFT,
};

typedef struct s_philo
{
	int				id;
	int				meal_count;
	long			time_to_die;
	long			last_meal_t;
	t_bool			sated;
	t_bool			*finish;
	t_args			args;
	pthread_t		thread_id;
	pthread_mutex_t	*finish_lock;
	pthread_mutex_t	sated_lock;
	pthread_mutex_t	last_meal_lock;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*fork[2];
}	t_philo;

typedef struct s_table
{
	t_bool			finish;
	t_args			*args;
	t_philo			**philos;
	pthread_t		reaper;
	pthread_mutex_t	finish_lock;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
}	t_table;

//	Input check
t_bool	correct_input(int argc, char **argv);
t_bool	ft_isdigit(char c);
t_bool	ft_issign(char c);
int		ft_atoi(const char *str);

//  Initialization
t_args	*fill_args(int argc, char **argv);
t_bool	create_philos(t_table *table);
t_bool	create_forks(t_table *table);

//	Time
long	get_time(void);
long	time_diff(long time);
void	better_usleep(long time);

//  Actions
t_bool	drop_forks(t_philo *philo);
t_bool	grab_two_forks(t_philo *philo);
t_bool	eating_philo(t_philo *philo);
t_bool	thinking_philo(t_philo *philo);
t_bool	sleeping_philo(t_philo *philo);
t_bool	dead_philo(t_table *table);

// Threads
t_bool	thread_create(t_table *table);
t_bool	table_destroy(t_table *table);

//	Cycle
void	*cycle(void *args);
void	*reap(void *table_ptr);
t_bool	printing_philo(t_philo *philo, char *color, char *status);

//	Error handling
void	exit_err(char *err);
void	err_hndl(char *err, t_table *table);
void	free_table(t_table *table);
#endif
