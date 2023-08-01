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

int	main(int argc, char **argv)
{
	t_table	*table;

	if (!correct_input(argc, argv))
		exit_err("Invalid Arguments.\n");
	table = set_table(argc, argv);
	table->t0 = get_time();
	usleep(1000000);
	printf("Current Time = %ld\nTime = %ld\n", get_time(), table->t0);
	printf("Philosophers = %d\n", table->args->philo_n);
	free_table(table);
}
