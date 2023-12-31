/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 11:32:21 by m_kamal           #+#    #+#             */
/*   Updated: 2023/07/29 12:51:34 by m_kamal          ###   ########.fr       */
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
# define DIED "has died"

//Colors
# define RESET "\e[0m"
# define GREEN "\e[0;32m"
# define G_BLUE "\e[0;38;5;24m"
# define B_BLUE "\e[1;34m"
# define G_CYAN "\e[0;38;5;44m"
# define RED "\033[31;1m"

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_args
{
	int		philo_n;
	long	die_t;
	long	eat_t;
	long	sleep_t;
	int		meals_n;
}	t_args;

typedef struct s_fork
{
	int	left;
	int	right;
}	t_fork;

typedef struct s_philo
{
	int			id;
	int			meal_count;
	long		time_to_die;
	t_fork		fork;
	pthread_t	thread;
}	t_philo;

typedef struct s_table
{
	int				n_thread;
	int				dead_philo;
	long			t0;
	t_args			*args;
	t_philo			*philos;
	pthread_t		maestro;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
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
void	exec_action(long time);

//  Actions
t_bool	drop_forks(t_table *table, int i);
t_bool	eating_philo(t_table *table, int i);
t_bool	thinking_philo(t_table *table, int i);
t_bool	sleeping_philo(t_table *table, int i);
t_bool	dead_philo(t_table *table, int *i);

// Threads
t_bool	thread_join(t_table *table);
t_bool	thread_create(t_table *table);
t_bool	thread_destroy(t_table *table);

//	Cycle
void	*cycle(void *args);
t_bool	cycle_execute(t_table *table, int i);
void	*checker(void *args);
t_bool	printing_philo(t_table *table, int ph_id, char *color, char *status);

//	Error handling
void	exit_err(char *err);
void	err_hndl(char *err, t_table *table);
void	free_table(t_table *table);
#endif
