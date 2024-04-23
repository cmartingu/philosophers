/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:15:44 by carlos-m          #+#    #+#             */
/*   Updated: 2024/04/16 12:15:45 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int	signo;
	int	nb;

	signo = 1;
	if (!str || str[0] == '\0')
		return (0);
	while (((*str >= 9) && (*str <= 13)) || (*str == 32))
		str++;
	if (*str == '-')
	{
		str++;
		signo = -1;
	}
	else if (*str == '+')
		str++;
	nb = 0;
	while ((*str >= '0') && (*str <= '9'))
	{
		nb = (nb * 10) + (int){*str - '0'};
		str++;
	}
	return (nb * signo);
}

int	do_atoi(int argc, char *argv[], t_datos *data)
{
	data->filo_quant = ft_atoi(argv[1]);
	data->ttd = ft_atoi(argv[2]);
	data->tte = ft_atoi(argv[3]);
	data->tts = ft_atoi(argv[4]);
	if (data->filo_quant <= 0 || data->ttd <= 0 || \
	data->tte <= 0 || data->tts <= 0)
	{
		printf("Error, invalid arguments\n");
		return (-1);
	}
	if (argc == 6)
	{
		data->min_time_eat = ft_atoi(argv[5]);
		if (data->min_time_eat <= 0)
		{
			printf("Error, invalid arguments\n");
			return (-1);
		}
	}
	else
		data->min_time_eat = -1;
	return (1);
}

t_datos	*parse_args(int argc, char *argv[])
{
	t_datos	*data;

	data = malloc(sizeof(t_datos));
	if (!data)
	{
		printf("Error, malloc error\n");
		return (NULL);
	}
	if (do_atoi(argc, argv, data) == -1)
		return (free(data), NULL);
	data->can_start = 0;
	data->one_dead = -1;
	pthread_mutex_init(&data->m_can_start, NULL);
	pthread_mutex_init(&data->m_dead, NULL);
	pthread_mutex_init(&data->m_write, NULL);
	return (data);
}

int	left_fork(int ind, int ind_max)
{
	if (ind == 0)
		return (ind_max);
	return (ind - 1);
}

t_philo	*ini_filo(t_general *general, int ind)
{
	t_philo	*filo;

	filo = malloc(sizeof(t_philo));
	if (!filo)
	{
		printf("Error, malloc error\n");
		return (NULL);
	}
	filo->filo_id = ind;
	filo->times_eaten = 0;
	filo->last_eat = 0;
	filo->l_fork = &(general->forks[left_fork(ind, \
	general->data->filo_quant - 1)]);
	filo->r_fork = &(general->forks[ind]);
	pthread_mutex_init(&filo->m_times_eaten, NULL);
	filo->data = general->data;
	return (filo);
}
