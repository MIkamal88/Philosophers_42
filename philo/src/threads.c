/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 21:01:22 by m_kamal           #+#    #+#             */
/*   Updated: 2023/10/16 21:01:22 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	thread_join(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->args->philo_n)
		if (pthread_join(table->philos[i]->thread_id, NULL))
			return (FALSE);
	if (pthread_join(table->reaper, NULL))
		return (FALSE);
	return (TRUE);
}

t_bool	thread_create(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->args->philo_n)
		if (pthread_create(&table->philos[i]->thread_id,
				NULL, cycle, table->philos[i]))
			return (FALSE);
	if (pthread_create(&table->reaper, NULL, reap, table))
		return (FALSE);
	if (thread_join(table) == FALSE)
		return (FALSE);
	return (TRUE);
}

t_bool	table_destroy(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->args->philo_n)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philos[i]->sated_lock);
		free(table->philos[i]);
	}
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->finish_lock);
	return (TRUE);
}
