/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 08:50:43 by m_kamal           #+#    #+#             */
/*   Updated: 2023/07/19 08:50:47 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_err(char *err)
{
	printf("%s", err);
	exit(1);
}

void	free_table(t_table *table)
{
	if (table->args != NULL)
		free(table->args);
	if (table->philos != NULL)
		free(table->philos);
	if (table->forks != NULL)
		free(table->forks);
}

void	err_hndl(char *err, t_table *table)
{
	free_table(table);
	printf("%s", err);
	exit(1);
}
