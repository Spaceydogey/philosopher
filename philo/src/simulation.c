/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:35:33 by hdelmas           #+#    #+#             */
/*   Updated: 2023/01/27 15:48:29 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	philo_eat(t_data *philo)
{
	if (pthread_mutex_lock(philo->l_fork) != 0)
		return (1);
	print_log(FORK, philo);
	if (pthread_mutex_lock(philo->r_fork) != 0)
		return (1);
	print_log(FORK, philo);
	print_log(EAT, philo);
	p_sleep(philo->args.time_to_eat);
	if (pthread_mutex_unlock(philo->l_fork) != 0)
		return (2);
	if (pthread_mutex_unlock(philo->r_fork) != 0)
		return (2);
	return (0);
}

int	check_if_dead(pthread_t *pth, t_data *philo_data)
{

}

void	*simulation(void *data)
{
	t_data	*philo;
	int		time;
	int		i;

	philo = (t_data *)data;
	i = -1;
	while (++i < philo->args.nbr_to_eat || philo->args.nbr_to_eat < 0)
	{
		print_log(THINK, philo);
		philo_eat(philo);
		print_log(SLEEP, philo);
		p_sleep(philo->args.time_to_sleep);
	}
	return (NULL);
}
