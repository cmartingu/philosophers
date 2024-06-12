/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:40:09 by carlos-m          #+#    #+#             */
/*   Updated: 2024/05/03 14:40:10 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	finish(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_can_start);
	if (philo->data->end)
	{
		pthread_mutex_unlock(&philo->data->m_can_start);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->m_can_start);
	return (0);
}

int	finish_eating(t_general *general)
{
	int	i;

	i = 0;
	while (i < general->data->num_philo)
	{
		pthread_mutex_lock(&general->philos[i].m_times_eat);
		if (general->philos[i].times_eaten < general->data->times_to_eat)
		{
			pthread_mutex_unlock(&general->philos[i].m_times_eat);
			return (0);
		}
		pthread_mutex_unlock(&general->philos[i].m_times_eat);
		i++;
	}
	return (1);
}

void	print_die(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->m_write);
	time = get_time_in_ms();
	if (finish(philo))
	{
		pthread_mutex_unlock(&philo->data->m_write);
		return ;
	}
	printf("%lu %d died\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->m_write);
}

int	control_finish(t_general *general)
{
	int	i;

	i = 0;
	while (i < general->data->num_philo)
	{
		pthread_mutex_lock(&general->data->m_last_eat_time);
		if (get_time_in_ms() - general->philos[i].last_eat >= \
		general->data->ttd)
		{
			print_die(&(general->philos[i]));
			pthread_mutex_unlock(&general->data->m_last_eat_time);
			return (1);
		}
		pthread_mutex_unlock(&general->data->m_last_eat_time);
		if (general->data->times_to_eat != -1 && finish_eating(general))
			return (1);
		i++;
	}
	return (0);
}

void	*hilo_control(t_general *general)
{
	int	start;

	while (1)
	{
		pthread_mutex_lock(&general->data->m_can_start);
		start = general->data->can_start;
		pthread_mutex_unlock(&general->data->m_can_start);
		if (start)
			break ;
	}
	while (1)
	{
		if (control_finish(general))
		{
			pthread_mutex_lock(&general->data->m_can_start);
			general->data->end = 1;
			pthread_mutex_unlock(&general->data->m_can_start);
			break ;
		}
	}
	return (NULL);
}
