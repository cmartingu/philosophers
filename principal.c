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

void	one_philo(t_general *general)
{
	int	aux_time;

	general->data->ini_time = get_time_in_ms();
	aux_time = get_time_in_ms() - general->data->ini_time;
	printf("%d 1 is thinking\n", aux_time);
	aux_time = get_time_in_ms() - general->data->ini_time;
	printf("%d 1 is has taken a fork\n", aux_time);
	usleep_functional(general->data->ttd);
	aux_time = get_time_in_ms() - general->data->ini_time;
	printf("%d 1 died\n", aux_time);
}

void	print_think(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->m_write);
	time = get_time_in_ms();
	if (finish(philo))
	{
		pthread_mutex_unlock(&philo->data->m_write);
		return ;
	}
	printf("%lu %d is thinking\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->m_write);
}

void	*principal(t_philo *philo)
{
	int		start;

	start = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->data->m_can_start);
		start = philo->data->can_start;
		pthread_mutex_unlock(&philo->data->m_can_start);
		if (start)
			break ;
	}
	usleep_functional(philo->id - 1);
	print_think(philo);
	while (1)
	{
		if (finish(philo))
			break ;
		eat_loop(philo);
	}
	return (NULL);
}

void	start_join(t_general *general)
{
	int	i;

	pthread_mutex_lock(&general->data->m_can_start);
	general->data->can_start = 1;
	pthread_mutex_unlock(&general->data->m_can_start);
	i = 0;
	while (i < general->data->num_philo)
	{
		pthread_join(general->hilos[i], NULL);
		i++;
	}
	pthread_join(general->hilo_aux, NULL);
}

void	start_program(t_general *general)
{
	int	i;

	general->data->can_start = 0;
	if (general->data->num_philo == 1)
	{
		one_philo(general);
		return ;
	}
	i = 0;
	while (i < general->data->num_philo)
	{
		general->philos[i].last_eat = get_time_in_ms();
		general->philos[i].times_eaten = 0;
		pthread_create(&(general->hilos[i]), NULL, \
		(void *)principal, &(general->philos[i]));
		i++;
	}
	pthread_create(&general->hilo_aux, NULL, (void *)hilo_control, general);
	general->data->ini_time = get_time_in_ms();
	start_join(general);
}
