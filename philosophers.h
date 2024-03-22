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

typedef struct s_philo
{
	pthread_t		*filosofos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	escr;
	int				num_philo;
	int				ttd;
	int				tte;
	int				tts;
	int				must_eat;
	int				dead;
}	t_philo;

typedef struct s_index_s
{
	int				value;
	t_philo			*filo;
}	t_index_s;

int		ft_atoi(const char *str);
t_philo	*parse_args(int argc, char *argv[]);

#endif