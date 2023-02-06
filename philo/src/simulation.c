/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:35:33 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/06 17:28:38 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	philo_eat(t_data *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_log(FORK, philo);
	if (philo->l_fork != philo->r_fork)
	{
		pthread_mutex_lock(philo->r_fork);
		print_log(FORK, philo);
		pthread_mutex_lock(philo->mutex.last_meal);
		philo->last_meal = get_time();
		pthread_mutex_unlock(philo->mutex.last_meal);
		print_log(EAT, philo);
		p_sleep(philo->args->time_to_eat);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	return (0);
}

static int	close_thread(t_data *philo)
{
	int	tmp;

	pthread_mutex_lock(philo->mutex.death_check);
	tmp = philo->args->status;
	pthread_mutex_unlock(philo->mutex.death_check);
	if (philo->args->status == DEAD)
		return (1);
	return (0);
}

void	*incr_philo_done(t_data *philo)
{
	pthread_mutex_lock(philo->mutex.done);
	philo->args->philo_done += 1;
	pthread_mutex_unlock(philo->mutex.done);
	return (NULL);
}

void	*simulation(void *data)
{
	t_data	*philo;
	int		i;

	philo = (t_data *)data;
	if (philo->id % 2 == 0)
		p_sleep(philo->args->time_to_eat / 2);
	i = -1;
	while (++i < philo->args->nbr_to_eat || philo->args->nbr_to_eat < 0)
	{
		if (close_thread(philo))
			break ;
		print_log(THINK, philo);
		if (close_thread(philo) || philo_eat(philo))
			break ;
		if (i == philo->args->nbr_to_eat - 1)
			incr_philo_done(philo);
		if (close_thread(philo))
			break ;
		print_log(SLEEP, philo);
		if (close_thread(philo))
			break ;
		p_sleep(philo->args->time_to_sleep);
	}
	return (0);
}
