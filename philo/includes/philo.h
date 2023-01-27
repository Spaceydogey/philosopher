/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:29:35 by hdelmas           #+#    #+#             */
/*   Updated: 2023/01/27 18:55:44 by hdelmas          ###   ########.fr       */
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

# define EAT "is eating"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define FORK "has taken a fork"
# define DIE "died"

# define DEAD 0
# define ALIVE 1

typedef struct s_args
{
	int		nbr_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nbr_to_eat;
	int		status;
	int		philo_done;
	size_t	start_time;
}	t_args;

typedef struct s_mutex
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death_check;
}	t_mutex;

typedef struct s_data
{
	int				id;
	size_t			last_meal;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_args			args;
	t_mutex			mutex;
}	t_data;

typedef struct timeval	t_timeval;

t_args	parse(char **av);
int		parse_error(t_args args);
int		ph_error(int err);
void	ft_putstr_fd(char *s, int fd);
int		init_mutex(pthread_mutex_t *tab, int nbr_philo);
int		init_mutex_tab(pthread_mutex_t **tab, int nbr_philo);
int		free_mutex_tab(pthread_mutex_t *tab, int nbr_philo);
int		philo(t_args args, t_mutex mutex);
size_t	get_time(void);
void	p_sleep(size_t	dt);
size_t	get_dtime(size_t start_ms);
int		print_log(char *msg, t_data *philo);
void	*simulation(void *data);
int		check_if_dead(pthread_t *pth, t_data *philo_data, t_args args);

#endif
