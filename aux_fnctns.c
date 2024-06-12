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

size_t	get_time_in_ms(void)
{
	size_t			sol;
	struct timeval	time;

	gettimeofday(&time, NULL);
	sol = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (sol);
}

void	usleep_functional(size_t time)
{
	size_t	begin;

	begin = get_time_in_ms();
	while (get_time_in_ms() - begin < time)
		usleep(250);
}

void	ft_free(t_general *general)
{
	int	i;

	i = 0;
	while (i < general->data->num_philo)
	{
		pthread_mutex_destroy(&(general->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(general->data->m_write));
	free(general->hilos);
	free(general->forks);
	free(general->data);
}

void	print_sleep(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->m_write);
	time = get_time_in_ms();
	if (finish(philo))
	{
		pthread_mutex_unlock(&philo->data->m_write);
		return ;
	}
	printf("%lu %d is sleeping\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->m_write);
}

void	print_eat(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->m_write);
	time = get_time_in_ms();
	if (finish(philo))
	{
		pthread_mutex_unlock(&philo->data->m_write);
		return ;
	}
	printf("%lu %d is eating\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->m_write);
}
