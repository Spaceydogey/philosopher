/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_dead.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 23:29:16 by hdelmas           #+#    #+#             */
/*   Updated: 2023/01/28 19:53:29 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	philo_set_status(t_data *philo_data, int i)
{
	if (pthread_mutex_lock(philo_data[i].mutex.death_check) != 0)
		return (-1);
	philo_data->args->status = DEAD;
	pthread_mutex_unlock(philo_data[i].mutex.death_check);
	return (0);
}

static int	philo_check__if_done(t_data *philo_data, t_args *args)
{
	if (pthread_mutex_lock(philo_data->mutex.done) != 0)
		return (1);
	
	if (args->philo_done == args->nbr_philo)
	{
		pthread_mutex_unlock(philo_data->mutex.done);
		return (0);
	}
	pthread_mutex_unlock(philo_data->mutex.done);
	return (1);
}

static int	philo_alive(pthread_t *pth, t_data *philo_data, t_args *args)
{
	int	res;
	int	i;
	int	is_done;

	res = args->nbr_philo;
	i = -1;
	while (++i < args->nbr_philo)
	{
		is_done = philo_check__if_done(philo_data, args);
		if (!is_done)
			return (is_done);
		if (pthread_mutex_lock(philo_data->mutex.death_check) != 0)
			return (-1);
		if (get_dtime(philo_data[i].last_meal) >= (size_t)args->time_to_die)
		{
			pthread_mutex_unlock(philo_data->mutex.death_check);
			res -= 1;
			print_log(DIE, &philo_data[i]);
			if (philo_set_status(philo_data, i) < 0)
				return (-1);
			break ;
		}
		pthread_mutex_unlock(philo_data->mutex.death_check);
	}
	return (res);
}

int	check_if_dead(pthread_t *pth, t_data *philo_data, t_args *args)
{
	while (philo_alive(pth, philo_data, args) == args->nbr_philo)
		;
	return (0);
}
