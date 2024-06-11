/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:28:38 by carlos-m          #+#    #+#             */
/*   Updated: 2024/05/03 15:28:40 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	new_atoi(char *str)
{
	int	final;

	if (!str || str[0] == '\0')
		return (0);
	final = 0;
	while (*str && *str >= '0' && *str <= '9')
	{
		final += *str - '0';
		final *= 10;
		str++;
	}
	final /= 10;
	return (final);
}

int	parse_args(char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		if (new_atoi(argv[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

t_datos	*ini_datos(char *argv[], int argc)
{
	t_datos	*data;

	data = malloc(sizeof(t_datos));
	data->num_philo = new_atoi(argv[1]);
	data->ttd = new_atoi(argv[2]);
	data->tte = new_atoi(argv[3]);
	data->tts = new_atoi(argv[4]);
	if (argc == 6)
		data->times_to_eat = new_atoi(argv[5]);
	else
		data->times_to_eat = -1;
	pthread_mutex_init((pthread_mutex_t *)(&data->m_write), NULL);
	pthread_mutex_init((pthread_mutex_t *)(&data->m_last_eat_time), NULL);
	data->end = 0;
	return (data);
}

void	ini_each_philo(t_general *general)
{
	int	i;

	i = 0;
	while (i < general->data->num_philo)
	{
		general->philos[i].data = general->data;
		general->philos[i].id = i + 1;
		general->philos[i].l_fork = &general->forks[i];
		if (i == general->data->num_philo - 1)
			general->philos[i].r_fork = &(general->forks[0]);
		else
			general->philos[i].r_fork = &(general->forks[i + 1]);
		pthread_mutex_init((pthread_mutex_t *) \
		(&general->philos[i].m_times_eat), NULL);
		i++;
	}
}

void	ini_general(t_general *all, char *argv[], int argc)
{
	int	i;

	all->data = ini_datos(argv, argc);
	all->hilos = malloc (sizeof(pthread_t) * (all->data->num_philo));
	if (!all->hilos)
		return ;
	all->forks = malloc (sizeof(pthread_mutex_t) * \
	(all->data->num_philo));
	if (!all->forks)
		return ;
	all->philos = malloc (sizeof(t_philo) * (all->data->num_philo));
	if (!all->forks)
		return ;
	i = 0;
	while (i < all->data->num_philo)
	{
		pthread_mutex_init(&(all->forks[i]), NULL);
		i++;
	}
	pthread_mutex_init((pthread_mutex_t *)(&all->data->m_can_start), NULL);
	ini_each_philo(all);
}
