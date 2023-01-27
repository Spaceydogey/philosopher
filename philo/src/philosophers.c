/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:06:09 by hdelmas           #+#    #+#             */
/*   Updated: 2023/01/28 00:06:22 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	philo_destroy(pthread_t *pth, int nbr_philo)
{
	int	i;

	i = -1;
	while (++i < nbr_philo)
	{
		if (pthread_join(pth[i], NULL) != 0)
			return (3);
	}
	return (2);
}

static t_data	philo_data_init(t_args *args, t_mutex mutex, int i)
{
	t_data	res;

	res.id = i + 1;
	res.args = args;
	res.mutex = mutex;
	res.last_meal = args->start_time;
	res.l_fork = &mutex.forks[i];
	res.r_fork = &mutex.forks[(i + 1) % args->nbr_philo];
	return (res);
}

int	philo(t_args args, t_mutex mutex)
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
		philo_data[i] = philo_data_init(&args, mutex, i);
		if (pthread_create(&pth[i], NULL, &simulation,
				&philo_data[i]) != 0)
			return (philo_destroy(pth, i));
	}
	check_if_dead(pth, philo_data, &args);
	philo_destroy(pth, args.nbr_philo);
	free(philo_data);
	free(pth);
	return (0);
}
