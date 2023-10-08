/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 08:49:38 by m_kamal           #+#    #+#             */
/*   Updated: 2023/08/12 09:38:38 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*cycle(void *args)
{
	t_table	*table;
	int		i;

	table = (t_table *)args;
	i = table->n_thread;
	if (table->args->meals_n > 0)
	{
		while (table->args->meals_n > table->philos[i].meal_count
			&& table->dead_philo == FALSE)
			cycle_execute(table, i);
	}
	else
	{
		while (table->dead_philo == FALSE)
		{
			if (cycle_execute(table, i) == FALSE)
				break ;
		}
	}
	return (NULL);
}

t_bool	cycle_execute(t_table *table, int i)
{
	if (eating_philo(table, i) == FALSE)
		return (FALSE);
	if (table->philos[i].meal_count != table->args->meals_n)
	{
		if (sleeping_philo(table, i) == FALSE)
			return (FALSE);
		if (thinking_philo(table, i) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

void	*checker(void *args)
{
	t_table	*table;
	int		i;

	table = (t_table *)args;
	i = 0;
	if (table->args->meals_n > 0)
	{
		while (table->args->meals_n > table->philos[i].meal_count
			&& table->dead_philo == FALSE)
		{
			if (dead_philo(table, &i) == TRUE)
				break ;
		}
	}
	else
	{
		while (table->dead_philo == FALSE)
		{
			if (dead_philo(table, &i) == TRUE)
				break ;
		}
	}
	return (NULL);
}

t_bool	printing_philo(t_table *table, int ph_id, char *color, char *status)
{
	long	now_t;

	now_t = time_diff(table->t0);
	if (table->dead_philo == TRUE)
		return (FALSE);
	pthread_mutex_lock(&table->write);
	if (table->dead_philo == TRUE)
	{
		pthread_mutex_unlock(&table->write);
		return (FALSE);
	}
	else
		printf("%s%-10ld %-3d %-30s%s\n", color, now_t, ph_id, status, RESET);
	pthread_mutex_unlock(&table->write);
	return (TRUE);
}
