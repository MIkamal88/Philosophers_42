/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 19:06:25 by m_kamal           #+#    #+#             */
/*   Updated: 2023/10/07 19:06:25 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	thread_create(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->args->philo_n)
	{
		table->n_thread = i;
		if (pthread_create(&table->philos[i].thread,
				NULL, &cycle, (void *) table) != 0)
			return (FALSE);
		i++;
		usleep(1000);
	}
	if (pthread_create(&table->maestro, NULL, &checker, (void *) table) != 0)
		return (FALSE);
	if (thread_join(table) == FALSE)
		return (FALSE);
	return (TRUE);
}

t_bool	thread_join(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->args->philo_n)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			return (FALSE);
		i++;
	}
	if (pthread_join(table->maestro, NULL) != 0)
		return (FALSE);
	return (TRUE);
}

t_bool	thread_destroy(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->args->philo_n)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->write);
	return (TRUE);
}
