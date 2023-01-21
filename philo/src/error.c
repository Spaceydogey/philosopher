/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:30:27 by hdelmas           #+#    #+#             */
/*   Updated: 2023/01/21 16:22:00 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	print_error(char *str)
{
	ft_putstr_fd("Error : ", 2);
	if (!str)
		return ;
	ft_putstr_fd(str, 2);
	write(2, "\n", 1);
}

int	ph_error(int err)
{
	if (err == 1)
		print_error("Wrong arguments");
	if (err == 2)
		print_error("Wrong number of arguments");
	return (1);
}
