/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:25:52 by m_kamal           #+#    #+#             */
/*   Updated: 2023/10/16 16:25:52 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	done_eating(t_table *table)
{
	int		i;
	t_bool	sated;

	i = -1;
	if (table->args->meals_n == -1)
		return (FALSE);
	while (++i < table->args->philo_n)
	{
		pthread_mutex_lock(&table->philos[i]->sated_lock);
		sated = table->philos[i]->sated;
		pthread_mutex_unlock(&table->philos[i]->sated_lock);
		if (!sated)
			return (FALSE);
	}
	pthread_mutex_lock(&table->finish_lock);
	table->finish = TRUE;
	pthread_mutex_unlock(&table->finish_lock);
	return (TRUE);
}

void	*reap(void *table_ptr)
{
	t_table	*table;
	t_bool	finish;

	table = (t_table *)table_ptr;
	pthread_mutex_lock(&table->finish_lock);
	finish = table->finish;
	pthread_mutex_unlock(&table->finish_lock);
	if (finish)
		return (NULL);
	while (done_eating(table) == FALSE)
	{
		if (dead_philo(table) == TRUE)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

static t_bool	cycle_execute(t_philo *philo)
{
	if (eating_philo(philo) == FALSE)
		return (FALSE);
	if (sleeping_philo(philo) == FALSE)
		return (FALSE);
	if (thinking_philo(philo) == FALSE)
		return (FALSE);
	return (TRUE);
}

static t_bool	is_meal_over(t_philo *philo)
{
	t_bool	finish;
	t_bool	sated;

	pthread_mutex_lock(philo->finish_lock);
	finish = *philo->finish;
	pthread_mutex_unlock(philo->finish_lock);
	if (finish)
		return (TRUE);
	pthread_mutex_lock(&philo->sated_lock);
	sated = philo->sated;
	pthread_mutex_unlock(&philo->sated_lock);
	if (sated)
		return (TRUE);
	return (FALSE);
}

void	*cycle(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	if (philo->args.philo_n == 1)
	{
		printing_philo(philo, YELLOW, FORK);
		usleep(philo->args.die_t * 1000);
		return (NULL);
	}
	while (!is_meal_over(philo))
		cycle_execute(philo);
	return (NULL);
}
