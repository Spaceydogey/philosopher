/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:03:52 by hdelmas           #+#    #+#             */
/*   Updated: 2023/01/11 16:35:03 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_args	args;

	args = parse(av);
	if (parse_error(args) == 1)
		return (1);
	printf("%d\n", args.nbr_philo);
	return (0);
}
