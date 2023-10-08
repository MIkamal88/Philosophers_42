/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 11:32:09 by m_kamal           #+#    #+#             */
/*   Updated: 2023/07/29 14:07:14 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Arguments:
//num_philo - time_to_die - time_to_eat - time_to_sleep - num_meals
static t_table	*set_table(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	table->args = fill_args(argc, argv);
	if (create_philos(table) == FALSE)
		err_hndl("Error Setting Philosophers.\n", table);
	if (create_forks(table) == FALSE)
		err_hndl("Error Setting Forks.\n", table);
	return (table);
}

static t_bool	one_philo(t_table *table)
{
	table->dead_philo = FALSE;
	if (pthread_mutex_init(&table->write, NULL) != 0)
		return (FALSE);
	table->t0 = get_time();
	printing_philo(table, 1, G_CYAN, FORK);
	usleep(table->args->die_t * 1000);
	printing_philo(table, 1, RED, DIED);
	free_table(table);
	return (TRUE);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	if (!correct_input(argc, argv))
		exit_err("Invalid Arguments.\n");
	table = set_table(argc, argv);
	if (table->args->philo_n == 1)
	{
		if (one_philo(table) == FALSE)
			return (1);
		return (0);
	}
	if (thread_create(table) == FALSE)
		return (1);
	if (thread_destroy(table) == FALSE)
		return (1);
	free_table(table);
	return (0);
}
