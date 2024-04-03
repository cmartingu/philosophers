/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:32:20 by carlos-m          #+#    #+#             */
/*   Updated: 2024/03/13 15:32:21 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_times
{
	int	ttd;
	int	tte;
	int	tts;
}	t_times;

typedef struct s_philo
{
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	escr;
	pthread_mutex_t check_dead;
	t_times			*times;
	int				num_philo;
	int				must_eat;
	int				ind_filo;
}	t_philo;

typedef struct s_index_s
{
	t_philo			*filo;
	int				*dead;
}	t_index_s;

int			parse(int argc, char *argv[]);
int			ft_atoi(const char *str);
void		print_message(int i, char *msg, pthread_mutex_t escr);
long long	get_time_in_ms(void);
int			left_fork(int ind, int ind_max);
int			right_fork(int ind, int ind_max);
t_times		*ini_times(char *argv[]);
t_index_s	*ini_index(char *argv[], int index, pthread_mutex_t **forks, pthread_mutex_t *escr, int *dead, pthread_mutex_t *check);

#endif