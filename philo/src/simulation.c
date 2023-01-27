/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:35:33 by hdelmas           #+#    #+#             */
/*   Updated: 2023/01/27 19:10:35 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	philo_eat(t_data *philo)
{
	if (pthread_mutex_lock(philo->l_fork) != 0)
		return (1);
	print_log(FORK, philo);
	if (philo->l_fork != philo->r_fork)
	{
		if (pthread_mutex_lock(philo->r_fork) != 0)
			return (1);
		print_log(FORK, philo);
		philo->last_meal = get_time();
		print_log(EAT, philo);
		p_sleep(philo->args.time_to_eat);
		if (pthread_mutex_unlock(philo->r_fork) != 0)
			return (2);
	}
	if (pthread_mutex_unlock(philo->l_fork) != 0)
		return (2);
	return (0);
}

static int	philo_alive(pthread_t *pth, t_data *philo_data, t_args args)
{
	int	res;
	int	i;

	res = args.nbr_philo;
	i = -1;
	while (++i < args.nbr_philo)
	{
		if (pthread_mutex_lock(&philo_data[i].mutex.death_check) != 0)
				return (-1) ;
		if (philo_data[i].args.philo_done != args.nbr_philo)
		{
			pthread_mutex_unlock(&philo_data[i].mutex.death_check);
			if (get_dtime(philo_data[i].last_meal) > (size_t)args.time_to_die && philo_data != 0)
			{
				res -= 1;
				print_log(DIE, &philo_data[i]);
				if (pthread_mutex_lock(&philo_data[i].mutex.death_check) != 0)
					return (0);
				philo_data->args.status = DEAD;
				pthread_mutex_unlock(&philo_data[i].mutex.death_check);
				break ;
			}
		}
		else
			pthread_mutex_unlock(&philo_data[i].mutex.death_check);
	}
	return (res);
}

int	check_if_dead(pthread_t *pth, t_data *philo_data, t_args args)
{
	while (philo_alive(pth, philo_data, args) == args.nbr_philo)
		;
	return (0);
}

void	*simulation(void *data)
{
	t_data	*philo;
	int		time;
	int		i;

	philo = (t_data *)data;
	if (philo->id % 2 == 0)
		p_sleep(philo->args.time_to_eat / 2);
	i = -1;
	while (++i < philo->args.nbr_to_eat || philo->args.nbr_to_eat < 0)
	{
		if (pthread_mutex_lock(&philo->mutex.death_check) != 0)
			break ;
		if (philo->args.status == DEAD)
		{	
			pthread_mutex_unlock(&philo->mutex.death_check);
			break ;
		}
		pthread_mutex_unlock(&philo->mutex.death_check);
		print_log(THINK, philo);
		philo_eat(philo);
		print_log(SLEEP, philo);
		p_sleep(philo->args.time_to_sleep);
	}
	if (pthread_mutex_lock(&philo->mutex.death_check) != 0)
			return (NULL) ;
	philo->args.philo_done += 1;
	pthread_mutex_unlock(&philo->mutex.death_check);
	return (NULL);
}
