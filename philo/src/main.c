/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:29:17 by m_kamal           #+#    #+#             */
/*   Updated: 2023/10/15 17:29:17 by m_kamal          ###   ########.fr       */
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
	if (create_forks(table) == FALSE)
		err_hndl("Error Setting Forks.\n", table);
	if (create_philos(table) == FALSE)
		err_hndl("Error Setting Philosophers.\n", table);
	table->finish = FALSE;
	pthread_mutex_init(&table->write_lock, NULL);
	pthread_mutex_init(&table->finish_lock, NULL);
	return (table);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	if (!correct_input(argc, argv))
		exit_err("Invalid Arguments.\n");
	table = set_table(argc, argv);
	if (thread_create(table) == FALSE)
		return (1);
	if (table_destroy(table) == FALSE)
		return (1);
	free_table(table);
	return (0);
}
