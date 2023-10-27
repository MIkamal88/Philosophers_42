/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:03:17 by m_kamal           #+#    #+#             */
/*   Updated: 2023/10/16 20:03:17 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	eating_philo(t_philo *philo)
{
	if (grab_two_forks(philo) == FALSE)
		return (FALSE);
	printing_philo(philo, WHITE, EAT);
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal_t = get_time();
	pthread_mutex_unlock(&philo->last_meal_lock);
	better_usleep(philo->args.eat_t);
	if (drop_forks(philo) == FALSE)
		return (FALSE);
	return (TRUE);
}

t_bool	thinking_philo(t_philo *philo)
{
	t_bool	finish;

	pthread_mutex_lock(philo->finish_lock);
	finish = *philo->finish;
	pthread_mutex_unlock(philo->finish_lock);
	if (finish)
		return (FALSE);
	if (printing_philo(philo, GREEN, THINK) == FALSE)
		return (FALSE);
	return (TRUE);
}

t_bool	sleeping_philo(t_philo *philo)
{
	t_bool	finish;

	pthread_mutex_lock(philo->finish_lock);
	finish = *philo->finish;
	pthread_mutex_unlock(philo->finish_lock);
	if (finish)
		return (FALSE);
	if (printing_philo(philo, B_BLUE, SLEEP) == FALSE)
		return (FALSE);
	better_usleep(philo->args.sleep_t);
	return (TRUE);
}

t_bool	dead_philo(t_table *table)
{
	int		i;
	long	since_last_meal_t;

	i = -1;
	while (++i < table->args->philo_n)
	{
		pthread_mutex_lock(&table->philos[i]->last_meal_lock);
		since_last_meal_t = time_diff(table->philos[i]->last_meal_t);
		pthread_mutex_unlock(&table->philos[i]->last_meal_lock);
		if (since_last_meal_t >= table->args->die_t)
		{
			pthread_mutex_lock(&table->finish_lock);
			table->finish = TRUE;
			pthread_mutex_unlock(&table->finish_lock);
			printing_philo(table->philos[i], RED, DIED);
			return (TRUE);
		}
	}
	return (FALSE);
}

t_bool	printing_philo(t_philo *philo, char *color, char *status)
{
	long	now_t;

	pthread_mutex_lock(philo->write_lock);
	now_t = time_diff(philo->args.t0);
	printf("%s%-10ld %-3d %-30s%s\n", color, now_t, philo->id, status, RESET);
	pthread_mutex_unlock(philo->write_lock);
	return (TRUE);
}
