/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:29:35 by hdelmas           #+#    #+#             */
/*   Updated: 2023/01/21 17:19:05 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h> 
# include <pthread.h>
# include <sys/time.h>

typedef struct s_args
{
	int		nbr_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nbr_to_eat;
	size_t	start_time;
}	t_args;

typedef struct s_data
{
	int	id;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	l_fork;
	t_args	args;
}	t_data;

typedef struct timeval t_timeval;
t_args  parse(char **av);
int 	parse_error(t_args args);
int 	ph_error(int err);
void	ft_putstr_fd(char *s, int fd);
int		init_mutex(pthread_mutex_t *tab, int nbr_philo);
int		init_mutex_tab(pthread_mutex_t **tab, int nbr_philo);
int		free_mutex_tab(pthread_mutex_t *tab, int nbr_philo);
void 	*simulation(void *data);
int		philo(t_args args, pthread_mutex_t *mutex_tab);

#endif
