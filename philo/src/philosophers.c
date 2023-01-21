/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:06:09 by hdelmas           #+#    #+#             */
/*   Updated: 2023/01/21 16:19:55 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	philo_destroy(pthread_t *pth, int nbr_philo)
{
	int	i;

	i = -1;
	while (++i < nbr_philo)
		if (pthread_join(pth[i], NULL) != 0)
			return (3);
	return (2);
}

static t_data	philo_data_init(t_args args, pthread_mutex_t *mutex_tab, int i)
{
	t_data	res;

	res.id = i + 1;
	res.args = args;
	res.l_fork = mutex_tab[i];
	res.r_fork = mutex_tab[(i + 1) % args.nbr_philo];
	return (res);
}

int	philo(t_args args, pthread_mutex_t *mutex_tab)
{
	pthread_t	*pth;
	int			i;
	t_data		*philo_data;

	pth = malloc(sizeof(pthread_t) * args.nbr_philo);
	if (!pth)
		return (1);
	philo_data = malloc(sizeof(t_data) * args.nbr_philo);
	if (!philo_data)
		return (5);
	i = -1;
	while (++i < args.nbr_philo)
	{
		philo_data[i] = philo_data_init(args, mutex_tab, i);
		if (pthread_create(&pth[i], NULL, &simulation,
				(void *)&philo_data[i]) != 0)
			return (philo_destroy(pth, i));
	}
	if (philo_destroy(pth, args.nbr_philo) != 0)
		return (4);
	free(pth);
	return (0);
}
