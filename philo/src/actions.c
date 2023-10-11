/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 11:19:59 by m_kamal           #+#    #+#             */
/*   Updated: 2023/08/12 09:53:19 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	drop_forks(t_table *table, int i)
{
	if (pthread_mutex_unlock(&table->forks[table->philos[i].fork.left]))
		return (FALSE);
	if (pthread_mutex_unlock(&table->forks[table->philos[i].fork.right]))
		return (FALSE);
	table->philos[i].meal_count++;
	return (TRUE);
}

t_bool	eating_philo(t_table *table, int i)
{
	if (pthread_mutex_lock(&table->forks[table->philos[i].fork.left]) != 0)
		return (FALSE);
	if (printing_philo(table, table->philos[i].id, YELLOW, FORK) == FALSE)
		return (FALSE);
	if (pthread_mutex_lock(&table->forks[table->philos[i].fork.right]) != 0)
		return (FALSE);
	if (printing_philo(table, table->philos[i].id, YELLOW, FORK) == FALSE)
		return (FALSE);
	if (printing_philo(table, table->philos[i].id, G_CYAN, EAT) == FALSE)
		return (FALSE);
	table->philos[i].time_to_die = get_time();
	usleep(table->args->eat_t * 1000);
	drop_forks(table, i);
	return (TRUE);
}

t_bool	thinking_philo(t_table *table, int i)
{
	if (printing_philo(table, table->philos[i].id, GREEN, THINK) == FALSE)
		return (FALSE);
	return (TRUE);
}

t_bool	sleeping_philo(t_table *table, int i)
{
	if (printing_philo(table, table->philos[i].id, B_BLUE, SLEEP) == FALSE)
		return (FALSE);
	usleep(table->args->sleep_t * 1000);
	return (TRUE);
}

t_bool	dead_philo(t_table *table, int *i)
{
	int	time;

	if (*i == table->args->philo_n)
		*i = 0;
	time = time_diff(table->philos[*i].time_to_die);
	if (time > table->args->die_t)
	{
		printing_philo(table, table->philos[*i].id, RED, DIED);
		table->dead_philo = TRUE;
		return (TRUE);
	}
	i++;
	return (FALSE);
}
