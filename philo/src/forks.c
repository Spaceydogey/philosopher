/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 14:39:23 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/06 17:38:02 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	malloc_mutex(t_mutex *mutex)
{
	mutex->death_check = malloc(sizeof(pthread_mutex_t));
	if (!mutex->death_check)
		return (-3);
	mutex->print = malloc(sizeof(pthread_mutex_t));
	if (!mutex->print)
		return (-4);
	mutex->done = malloc(sizeof(pthread_mutex_t));
	if (!mutex->done)
		return (-5);
	mutex->last_meal = malloc(sizeof(pthread_mutex_t));
	if (!mutex->last_meal)
		return (-6);
	return (0);
}

int	init_mutex(t_mutex *mutex, int nbr_philo)
{	
	int	i;

	if (malloc_mutex(mutex) != 0)
		return (-3);
	i = -1;
	while (++i < nbr_philo)
	{
		if (pthread_mutex_init(&mutex->forks[i], NULL) != 0)
			break ;
	}
	if (pthread_mutex_init(mutex->death_check, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(mutex->print, NULL) != 0)
		return (-2);
	if (pthread_mutex_init(mutex->done, NULL) != 0)
		return (-4);
	if (pthread_mutex_init(mutex->last_meal, NULL) != 0)
		return (-5);
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
		pthread_mutex_destroy(mutex.death_check);
		pthread_mutex_destroy(mutex.print);
		pthread_mutex_destroy(mutex.done);
		pthread_mutex_destroy(mutex.last_meal);
		free(mutex.print);
		free(mutex.death_check);
		free(mutex.done);
		free(mutex.last_meal);
		return (6);
	}
	return (0);
}
