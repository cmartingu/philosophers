/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:39:10 by carlos-m          #+#    #+#             */
/*   Updated: 2024/03/22 12:39:11 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parse(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
		return (0);
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0 || \
	ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0)
		return (0);
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) <= 0)
			return (0);
	}
	return (1);
}

int	left_fork(int ind, int ind_max)
{
	if (ind == 0)
		return (ind_max);
	return (ind - 1);
}

int	right_fork(int ind, int ind_max)
{
	if (ind == ind_max)
		return (ind_max);
	return (ind);
}

t_times	*ini_times(char *argv[])
{
	t_times	*times;

	times = malloc(sizeof(t_times));
	if (!times)
	{
		printf("Error, malloc error\n");
		return (NULL);
	}
	times->ttd = ft_atoi(argv[2]);
	times->tte = ft_atoi(argv[3]);
	times->tts = ft_atoi(argv[4]);
	return (times);
}

t_index_s	*ini_index(char *argv[], int index, pthread_mutex_t **forks, pthread_mutex_t *escr, int *dead, pthread_mutex_t *check)
{
	t_index_s	*f_ind;

	f_ind = malloc(sizeof(t_index_s));
	if (!f_ind)
	{
		printf("Error, malloc error\n");
		return (NULL);
	}
	f_ind->dead =  dead;
	f_ind->filo = malloc(sizeof(t_philo));
	if (!f_ind->filo)
	{
		printf("Error, malloc error\n");
		return (free(f_ind), NULL);
	}
	f_ind->filo->escr = *escr;
	f_ind->filo->check_dead = *check;
	f_ind->filo->ind_filo = index;
	f_ind->filo->num_philo = ft_atoi(argv[1]);
	if (argv[5] != NULL)
		f_ind->filo->must_eat = ft_atoi(argv[5]);
	else
		f_ind->filo->must_eat = 0;
	f_ind->filo->l_fork = &((*forks)[left_fork(index, ft_atoi(argv[1]) - 1)]);
	f_ind->filo->r_fork = &((*forks)[right_fork(index, ft_atoi(argv[1]) - 1)]);
	f_ind->filo->times = ini_times(argv);
	if (!f_ind->filo->times)
		return (free(f_ind->filo), free(f_ind), NULL);
	return (f_ind);
}
