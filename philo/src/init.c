/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:31:32 by m_kamal           #+#    #+#             */
/*   Updated: 2023/10/15 17:31:32 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

t_args	*fill_args(int argc, char **args)
{
	t_args	*data;

	data = malloc(sizeof(t_args));
	data->t0 = get_time();
	data->philo_n = ft_atoi(args[1]);
	data->die_t = ft_atoi(args[2]);
	data->eat_t = ft_atoi(args[3]);
	data->sleep_t = ft_atoi(args[4]);
	data->meals_n = -1;
	if (argc == 6)
		data->meals_n = ft_atoi(args[5]);
	return (data);
}

static void	fill_philo_args(t_philo *philo, t_table *table)
{
	philo->args.t0 = table->args->t0;
	philo->args.meals_n = table->args->meals_n;
	philo->args.sleep_t = table->args->sleep_t;
	philo->args.die_t = table->args->die_t;
	philo->args.eat_t = table->args->eat_t;
	philo->args.philo_n = table->args->philo_n;
}

static t_bool	populate_philo(t_table *table, int i)
{
	table->philos[i] = malloc(sizeof(t_philo));
	if (!table->philos[i])
		return (FALSE);
	table->philos[i]->id = i + 1;
	table->philos[i]->meal_count = 0;
	table->philos[i]->time_to_die = 0;
	table->philos[i]->last_meal_t = get_time();
	table->philos[i]->sated = FALSE;
	table->philos[i]->finish = &table->finish;
	table->philos[i]->finish_lock = &table->finish_lock;
	table->philos[i]->write_lock = &table->write_lock;
	fill_philo_args(table->philos[i], table);
	pthread_mutex_init(&table->philos[i]->sated_lock, NULL);
	pthread_mutex_init(&table->philos[i]->last_meal_lock, NULL);
	table->philos[i]->fork[LEFT] = &table->forks[i];
	table->philos[i]->fork[RIGHT] = &table->forks[(i + 1) % \
		table->args->philo_n];
	return (TRUE);
}

t_bool	create_philos(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * (table->args->philo_n));
	if (!table->philos)
		return (FALSE);
	i = -1;
	while (++i < table->args->philo_n)
		populate_philo(table, i);
	return (TRUE);
}

t_bool	create_forks(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->args->philo_n);
	if (!table->forks)
		return (FALSE);
	i = -1;
	while (++i < table->args->philo_n)
		pthread_mutex_init(&table->forks[i], NULL);
	return (TRUE);
}
