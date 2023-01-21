/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:03:52 by hdelmas           #+#    #+#             */
/*   Updated: 2023/01/21 17:29:07 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	get_time(void)
{
	t_timeval	tv;
	size_t		res;

	if (gettimeofday(&tv, NULL) != 0)
		return (0);
	res = (tv.tv_sec * 1000) + (tv.tv_usec / 1000); 
	return (res);
}

void	*simulation(void *data)
{
	t_data	*philo;
	int		time;
	int		i = -1;

	philo = (t_data *)data;
	while (++i < 10)
	{
		printf("%d	%lu\n", philo->id, get_time() - philo->args.start_time);
		usleep(500);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_args			args;
	int				nbr_forks;
	pthread_mutex_t	*mutex_tab;

	if (ac < 5 || ac > 6)
		return (ph_error(2));
	args = parse(av);
	if (parse_error(args) == 1)
		return (2);
	args.start_time = get_time();
	if (init_mutex_tab(&mutex_tab, args.nbr_philo) != 0)
		return (3);
	nbr_forks = init_mutex(mutex_tab, args.nbr_philo);
	if (nbr_forks != args.nbr_philo)
		return (free_mutex_tab(mutex_tab, nbr_forks));
	philo(args, mutex_tab);
	free_mutex_tab(mutex_tab, args.nbr_philo);
	return (0);
}
