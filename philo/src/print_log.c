/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:07:13 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/06 11:07:46 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	print_log(char *msg, t_data *philo)
{
	size_t	dt;

	pthread_mutex_lock(philo->mutex.death_check);
	if (philo->args->status == DEAD)
	{
		pthread_mutex_unlock(philo->mutex.death_check);
		return (1);
	}
	pthread_mutex_unlock(philo->mutex.death_check);
	dt = get_dtime(philo->args->start_time);
	pthread_mutex_lock(philo->mutex.print);
	printf("%lu\t%d\t%s\n", dt, philo->id, msg);
	pthread_mutex_unlock(philo->mutex.print);
	return (0);
}
