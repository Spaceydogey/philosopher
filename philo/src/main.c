/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:03:52 by hdelmas           #+#    #+#             */
/*   Updated: 2023/01/28 19:58:55 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_args	args;
	int		nbr_forks;
	t_mutex	mutex;

	if (ac < 5 || ac > 6)
		return (ph_error(2));
	args = parse(av);
	if (parse_error(args) == 1)
		return (2);
	args.start_time = get_time();
	args.status = ALIVE;
	args.philo_done = 0;
	if (init_mutex_tab(&mutex.forks, args.nbr_philo) != 0)
		return (3);
	nbr_forks = init_mutex(&mutex, args.nbr_philo);
	if ((nbr_forks != args.nbr_philo && nbr_forks >= 0) || nbr_forks < 0)
		return (free_mutex(mutex, args.nbr_philo, nbr_forks));
	philo(args, mutex);
	free(mutex.print);
	free(mutex.death_check);
	free_mutex_tab(mutex.forks, args.nbr_philo);
	pthread_mutex_destroy(mutex.death_check);
	pthread_mutex_destroy(mutex.print);
	return (0);
}
