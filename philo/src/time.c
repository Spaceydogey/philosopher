/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:08:26 by hdelmas           #+#    #+#             */
/*   Updated: 2023/01/27 15:18:21 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	get_time(void)
{
	t_timeval	tv;
	size_t		res;

	if (gettimeofday(&tv, NULL) != 0)
		return (0);
	res = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (res);
}

void	p_sleep(size_t	dt)
{
	size_t	start_time;

	start_time = get_time();
	while (get_time() < start_time + dt)
		usleep(100);
	return ;
}

size_t	get_dtime(size_t start_ms)
{
	return (get_time() - start_ms);
}
