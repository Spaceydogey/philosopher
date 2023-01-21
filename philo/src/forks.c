/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 14:39:23 by hdelmas           #+#    #+#             */
/*   Updated: 2023/01/21 16:20:46 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_mutex(pthread_mutex_t *tab, int nbr_philo)
{	
	int	i;

	i = -1;
	while (++i < nbr_philo)
	{
		if (pthread_mutex_init(&tab[i], NULL) != 0)
			break ;
	}
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
