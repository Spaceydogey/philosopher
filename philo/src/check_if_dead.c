/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_dead.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 23:29:16 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/07 11:53:21 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	philo_set_status(t_data *philo_data, int i)
{
	pthread_mutex_lock(philo_data[i].mutex.death_check);
	philo_data->args->status = DEAD;
	pthread_mutex_unlock(philo_data[i].mutex.death_check);
	return (0);
}

static int	philo_check__if_done(t_data *philo_data, t_args *args)
{
	int	tmp;

	pthread_mutex_lock(philo_data->mutex.done);
	tmp = args->philo_done;
	pthread_mutex_unlock(philo_data->mutex.done);
	if (tmp == args->nbr_philo)
		return (0);
	return (1);
}

static int	philo_alive(pthread_t *pth, t_data *philo_data, t_args *args)
{
	int		res;
	int		i;
	int		is_done;
	size_t	last_meal_tmp;

	res = args->nbr_philo;
	i = -1;
	while (++i < args->nbr_philo)
	{
		is_done = philo_check__if_done(philo_data, args);
		if (!is_done)
			return (is_done);
		pthread_mutex_lock(philo_data[i].mutex.last_meal);
		last_meal_tmp = philo_data[i].last_meal;
		pthread_mutex_unlock(philo_data[i].mutex.last_meal);
		if (get_dtime(last_meal_tmp) > (size_t)args->time_to_die)
		{
			res -= 1;
			print_log(DIE, &philo_data[i]);
			philo_set_status(philo_data, i);
			break ;
		}
	}
	return (res);
}

int	check_if_dead(pthread_t *pth, t_data *philo_data, t_args *args)
{
	while (philo_alive(pth, philo_data, args) == args->nbr_philo)
		;
	return (0);
}
