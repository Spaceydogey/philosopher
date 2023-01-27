/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:07:13 by hdelmas           #+#    #+#             */
/*   Updated: 2023/01/27 13:23:57 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	print_log(char *msg, t_data *philo)
{
	size_t	dt;

	dt = get_dtime(philo->args.start_time);
	if (pthread_mutex_lock(&philo->mutex.print) != 0)
		return (1);
	printf("%lu\t%d\t%s\n", dt, philo->id, msg);
	pthread_mutex_unlock(&philo->mutex.print);
	return (0);
}
