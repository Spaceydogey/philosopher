/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 14:39:23 by hdelmas           #+#    #+#             */
/*   Updated: 2023/01/27 23:25:51 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_mutex(t_mutex *mutex, int nbr_philo)
{	
	int	i;

	i = -1;
	while (++i < nbr_philo)
	{
		if (pthread_mutex_init(&mutex->forks[i], NULL) != 0)
			break ;
	}
	if (pthread_mutex_init(&mutex->death_check, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&mutex->print, NULL) != 0)
		return (-2);
	return (i);
}

int	init_mutex_tab(pthread_mutex_t **tab, int nbr_philo)
{
	*tab = malloc(sizeof(pthread_mutex_t) * nbr_philo);
	if (!*tab)
		return (1);
	return (0);
}

int	free_mutex_tab(pthread_mutex_t *tab, int nbr_philo)
{
	int	i;

	i = -1;
	while (++i < nbr_philo)
		pthread_mutex_destroy(&tab[i]);
	free(tab);
	return (4);
}

int	free_mutex(t_mutex mutex, int nbr_philo, int nbr_forks)
{
	if (nbr_forks >= 0)
		return (free_mutex_tab(mutex.forks, nbr_forks));
	if (nbr_forks == -1)
	{
		free_mutex_tab(mutex.forks, nbr_philo);
		return (5);
	}
	if (nbr_forks == -2)
	{
		free_mutex_tab(mutex.forks, nbr_philo);
		pthread_mutex_destroy(&mutex.death_check);
		return (6);
	}
}
