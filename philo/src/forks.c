/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:40:45 by m_kamal           #+#    #+#             */
/*   Updated: 2023/10/13 17:40:45 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	grab_a_fork(t_philo *philo, int loc)
{
	t_bool	finish;

	pthread_mutex_lock(philo->fork[loc]);
	pthread_mutex_lock(philo->finish_lock);
	finish = *philo->finish;
	pthread_mutex_unlock(philo->finish_lock);
	if (finish)
	{
		pthread_mutex_unlock(philo->fork[loc]);
		return (FALSE);
	}
	if (printing_philo(philo, YELLOW, FORK) == FALSE)
		return (FALSE);
	return (TRUE);
}

t_bool	grab_two_forks(t_philo *philo)
{
	int	first;
	int	second;

	if (philo->id % 2 == 0)
	{
		first = RIGHT;
		second = LEFT;
	}
	else
	{
		first = LEFT;
		second = RIGHT;
	}
	if (!grab_a_fork(philo, first))
		return (FALSE);
	if (!grab_a_fork(philo, second))
	{
		pthread_mutex_unlock(philo->fork[first]);
		return (FALSE);
	}
	return (TRUE);
}

t_bool	drop_forks(t_philo *philo)
{
	if (pthread_mutex_unlock(philo->fork[LEFT]))
		return (FALSE);
	if (pthread_mutex_unlock(philo->fork[RIGHT]))
		return (FALSE);
	if (philo->meal_count == philo->args.meals_n)
	{
		pthread_mutex_lock(&philo->sated_lock);
		philo->sated = TRUE;
		pthread_mutex_unlock(&philo->sated_lock);
	}
	return (TRUE);
}
