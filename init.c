/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 08:50:24 by m_kamal           #+#    #+#             */
/*   Updated: 2023/07/29 14:17:51 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <bits/pthreadtypes.h>

//Arguments: argc 5 or 6
//exec - num_philo - time_to_die - time_to_eat - time_to_sleep - num_meals(OPT)
//    0			1			2			3			4			5
t_args	*fill_args(int argc, char **args)
{
	t_args	*data;

	data = malloc(sizeof(t_args));
	data->philo_n = ft_atoi(args[1]);
	data->die_t = ft_atoi(args[2]);
	data->eat_t = ft_atoi(args[3]);
	data->sleep_t = ft_atoi(args[4]);
	data->meals_n = -1;
	if (argc == 6)
		data->meals_n = ft_atoi(args[5]);
	return (data);
}

static void	populate_philo(t_table *table, int i, int j)
{
	table->philos[i].id = i + 1;
	table->philos[i].meal_count = 0;
	table->philos[i].time_to_die = 0;
	table->philos[i].fork.left = i;
	table->philos[i].fork.right = j;
}

t_bool	create_philos(t_table *table)
{
	int	i;
	int	j;

	table->philos = malloc(sizeof(t_philo) * (table->args->philo_n));
	if (table->philos == NULL)
		return (FALSE);
	i = 0;
	j = 1;
	while (j < table->args->philo_n)
	{
		populate_philo(table, i, j);
		i++;
		j++;
	}
	j = 0;
	populate_philo(table, i, j);
	return (TRUE);
}

t_bool	create_forks(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->args->philo_n + 1);
	if (table->forks == NULL)
		return (FALSE);
	i = 0;
	while (i < table->args->philo_n)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}
