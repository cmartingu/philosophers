/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:29:54 by carlos-m          #+#    #+#             */
/*   Updated: 2024/03/13 15:29:55 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*hilos(t_index_s *ind)
{
	int				ref_time;

	if (ind->filo->num_philo == 0)
		return (NULL);
	ref_time = 0;
	while (1)
	{
		pthread_mutex_lock(&ind->filo->check_dead);
		if (*(ind->dead) == 1)
		{
			pthread_mutex_unlock(&ind->filo->check_dead);
			return (NULL);
		}
		pthread_mutex_unlock(&ind->filo->check_dead);
		print_message(ind->filo->ind_filo, "is thinking", ind->filo->escr);
		usleep(ind->filo->times->tts * 1000);
		if (ref_time != 0)
		{
			ref_time = get_time_in_ms() - ref_time;
			if (ref_time >= ind->filo->times->ttd)
			{
				*(ind->dead) = 1;
				break ;
			}
		}
		pthread_mutex_lock(ind->filo->l_fork);
		print_message(ind->filo->ind_filo, "has taken a fork", ind->filo->escr);
		pthread_mutex_lock(ind->filo->r_fork);
		ref_time = get_time_in_ms();
		print_message(ind->filo->ind_filo, "has taken a fork", ind->filo->escr);
		pthread_mutex_lock(&ind->filo->check_dead);
		if (*(ind->dead) > 0)
		{
			pthread_mutex_unlock(ind->filo->l_fork);
			pthread_mutex_unlock(ind->filo->r_fork);
			pthread_mutex_unlock(&ind->filo->check_dead);
			return (NULL);
		}
		pthread_mutex_unlock(&ind->filo->check_dead);
		print_message(ind->filo->ind_filo, "is eating", ind->filo->escr);
		usleep(ind->filo->times->tte * 1000);
		pthread_mutex_unlock(ind->filo->l_fork);
		pthread_mutex_unlock(ind->filo->r_fork);
		print_message(ind->filo->ind_filo, "is sleeping", ind->filo->escr);
	}
	print_message(ind->filo->ind_filo, "died", ind->filo->escr);
	return (NULL);
}

int	main(int argc, char *argv[])
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	escr;
	pthread_mutex_t	check_dead;
	pthread_t		*filosofos;
	t_index_s		*f_ind;
	int				some_dead;
	int				i;

	if (parse(argc, argv) == 0)
	{
		printf("Error, remember to set the rigth arguments\n");
		return (1);
	}
	filosofos = malloc(ft_atoi(argv[1]));
	if (!filosofos)
	{
		printf("Error, malloc error\n");
		return (1);
	}
	forks = malloc(ft_atoi(argv[1]) * sizeof(pthread_mutex_t));
	if (!forks)
	{
		printf("Error, malloc error\n");
		return (1);
	}
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_mutex_init(&(forks[i]), NULL);
		i++;
	}
	pthread_mutex_init(&escr, NULL);
	pthread_mutex_init(&check_dead, NULL);
	i = 0;
	some_dead = 0;
	f_ind = malloc(ft_atoi(argv[1]) * sizeof(t_index_s *));
	if (!f_ind)
	{
		printf("Error, malloc error\n");
		return (1);
	}
	while (i < ft_atoi(argv[1]))
	{
		f_ind[i] = *ini_index(argv, i, &forks, &escr, &some_dead, &check_dead);
		pthread_create(&(filosofos[i]), NULL, (void *)hilos, (void *)(&f_ind[i]));
		i++;
	}
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_join(filosofos[i], NULL);
		i++;
	}
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_mutex_destroy(&(forks[i]));
		i++;
	}
	pthread_mutex_destroy(&escr);
	free(filosofos);
	free(forks);
	free(f_ind);
	return (0);
}
