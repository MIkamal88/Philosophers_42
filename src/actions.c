/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 11:19:59 by m_kamal           #+#    #+#             */
/*   Updated: 2023/08/01 11:54:27 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	philo_print(t_table *table, int ph_id, char *status)
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
		printf("%-10ld %-3d %-30s\n", now_t, ph_id, status);
	return (TRUE);
}

t_bool	philo_eat(t_table *table, int i)
{
	if (pthread_mutex_lock(&table->forks[table->philos[i].fork.left]) != 0)
		return (FALSE);

}
