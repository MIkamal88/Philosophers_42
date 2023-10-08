/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:27:45 by m_kamal           #+#    #+#             */
/*   Updated: 2023/07/29 14:31:18 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*  tv_sec is in seconds, tv_usec is microseconds
 *  1 sec = 1000ms         1 microsecond = 0.001ms*/
long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec * 0.001));
}

long	time_diff(long time)
{
	if (time > 0)
		return (get_time() - time);
	return (0);
}

t_bool	ft_isdigit(char c)
{
	if ((c >= '0' && c <= '9') || c == ' ')
		return (TRUE);
	return (FALSE);
}

t_bool	ft_issign(char c)
{
	if (c == '+' || c == '-')
		return (TRUE);
	return (FALSE);
}

int	ft_atoi(const char *str)
{
	int			i;
	long int	n;

	i = 0;
	n = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + str[i] - '0';
		i++;
	}
	if (n < 0 || ((str[i] < '0' || str[i] > '9') && str[i] != '\0')
		|| n > INT_MAX)
		return (0);
	return (n);
}
