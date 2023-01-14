/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:39:41 by hdelmas           #+#    #+#             */
/*   Updated: 2023/01/11 16:43:48 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_isspace(char c)
{
	if ((c == 32) || (c <= 13 && c >= 9))
		return (1);
	return (0);
}

static int	ph_atoi(const char *nptr)
{
	long int		res;
	int				sign;

	res = 0;
	sign = 1;
	while (ft_isspace(*nptr) == 1)
		nptr++;
	if (*nptr == 45 || *nptr == 43)
		if (*(nptr++) == 45)
			sign = -1;
	while (*nptr >= 48 && *nptr <= 57)
	{
		res = (10 * res + (*nptr - 48));
		if (res > INT_MAX)
			return (-1);
		nptr++;
	}
	if ((sign == -1 && res != 0) || (*nptr != '\0'))
		return (-1);
	return ((int)res);
}

t_args	parse(char **av)
{
	t_args	res;

	res.nbr_philo = ph_atoi(av[1]);
	res.time_to_die = ph_atoi(av[2]);
	res.time_to_eat = ph_atoi(av[3]);
	res.time_to_sleep = ph_atoi(av[4]);
	if (av[5])
		res.nbr_to_eat = ph_atoi(av[5]);
	else
		res.nbr_to_eat = -2;
	return (res);
}

int	parse_error(t_args args)
{
	if (args.nbr_philo < 1)
		return (ph_error(1));
	if (args.time_to_die < 1)
		return (ph_error(1));
	if (args.time_to_eat < 1)
		return (ph_error(1));
	if (args.time_to_sleep < 1)
		return (ph_error(1));
	if (args.nbr_to_eat != -2 && args.nbr_to_eat < 1)
		return (ph_error(1));
	return (0);
}
