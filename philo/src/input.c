/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 08:53:32 by m_kamal           #+#    #+#             */
/*   Updated: 2023/07/19 14:12:48 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Arguments: argc 5 or 6
//exec - num_philo - time_to_die - time_to_eat - time_to_sleep - num_meals(OPT)
//    0			1			2			3			4			5

static t_bool	check_ifnum(char **argv)
{
	int	i;
	int	j;

	j = 1;
	while (argv[j])
	{
		i = 0;
		if (ft_issign(argv[j][i]))
			i++;
		while (argv[j][i] && ft_isdigit(argv[j][i]))
			i++;
		if (argv[j][i] != '\0' && !ft_isdigit(argv[j][i]))
			return (FALSE);
		j++;
	}
	return (TRUE);
}

static t_bool	philo_check(char **argv)
{
	int	num_philo;

	num_philo = ft_atoi(argv[1]);
	if (!num_philo)
		return (FALSE);
	return (TRUE);
}

static t_bool	time_check(char **argv)
{
	int	time;
	int	i;

	i = 1;
	while (++i < 5)
	{
		time = ft_atoi(argv[i]);
		if (time <= 0)
			return (FALSE);
	}
	return (TRUE);
}

t_bool	correct_input(int argc, char **argv)
{
	t_bool	bool;

	bool = FALSE;
	if (argc != 5 && argc != 6)
		printf("Invalid number or arguments.\n");
	if (!check_ifnum(argv))
		printf("Arguments are not in correct format.\n");
	else if (!philo_check(argv))
		printf("Invalid number of philosphers.\n");
	else if (!time_check(argv))
		printf("Timestamp can't be negative value or null.\n");
	else
		bool = TRUE;
	return (bool);
}
