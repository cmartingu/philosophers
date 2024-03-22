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

long long get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec) * 1000 + (long long)(tv.tv_usec) / 1000);
}

void	print_message(int i, char *msg, pthread_mutex_t escr)
{
	pthread_mutex_lock(&escr);
	printf("%lld %d %s\n", get_time_in_ms(), i, msg);
	pthread_mutex_unlock(&escr);
}

int	left_fork(int ind, int ind_max)
{
	if (ind == 0)
		return (ind_max);
	return (ind - 1);
}

int	right_fork(int ind, int ind_max)//ind_max es num_philo - 1
{
	if (ind == ind_max)
		return (0);
	return (ind + 1);
}

void	*hilos(t_index_s *ind)
{
	if (ind->filo->num_philo == 0)
		return (NULL);
	while (1)
	{
		if (ind->filo->dead == 1)
			return (NULL);
		print_message(ind->value, "is thinking", ind->filo->escr);
		break ;
	}
	return (NULL);
}

t_index_s	*ini_index(t_philo **filos, int i)
{
	t_index_s	*ind;

	ind = malloc(sizeof(t_index_s));
	if (!ind)
	{
		printf("Error, malloc error");
		exit(1);
	}
	ind->value = i;
	ind->filo = *filos;
	return (ind);
}

int	main(int argc, char *argv[])
{
	t_philo			*filo;
	t_index_s		*ind;
	int				i;

	filo = parse_args(argc, argv);
	if (filo == NULL)
	{
		printf("Remember to set the right arguments\n");
		return (1);
	}
	filo->forks = malloc(filo->num_philo);
	if (!filo->forks)
	{
		printf("Error, malloc error");
		return (1);
	}
	i = 0;
	while (i < filo->num_philo)
	{
		pthread_mutex_init(&(filo->forks[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(filo->escr), NULL);
	filo->filosofos = malloc(filo->num_philo);
	if (!filo->filosofos)
	{
		printf("Error, malloc error");
		return (1);
	}
	i = 0;
	while (i < filo->num_philo)
	{
		ind = ini_index(&filo, i);
		pthread_create(&filo->filosofos[i], NULL, (void *)hilos, (void *)ind);
		free(ind);
		i++;
	}
	i = 0;
	while (i < filo->num_philo)
	{
		pthread_join(filo->filosofos[i], NULL);
		i++;
	}
	i = 0;
	while (i < filo->num_philo)
	{
		pthread_mutex_destroy(&(filo->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(filo->escr));
	free(filo->filosofos);
	free(filo);
	return (0);
}
