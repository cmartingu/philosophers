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

void	print_fork(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->m_write);
	time = get_time_in_ms();
	if (finish(philo))
	{
		pthread_mutex_unlock(&philo->data->m_write);
		return ;
	}
	printf("%lu %d has taken a fork\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->m_write);
}

void	lock_forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
		pthread_mutex_lock(philo->l_fork);
	else
		pthread_mutex_lock(philo->r_fork);
	if (finish(philo))
	{
		if (philo->id % 2 == 1)
			pthread_mutex_unlock(philo->l_fork);
		else
			pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	print_fork(philo);
	if (philo->id % 2 == 1)
		pthread_mutex_lock(philo->r_fork);
	else
		pthread_mutex_lock(philo->l_fork);
	if (finish(philo))
	{
		if (philo->id % 2 == 1)
			pthread_mutex_unlock(philo->r_fork);
		else
			pthread_mutex_unlock(philo->l_fork);
		return ;
	}
}

void	eat_loop(t_philo *philo)
{
	lock_forks(philo);
	print_fork(philo);
	print_eat(philo);
	pthread_mutex_lock(&philo->data->m_last_eat_time);
	philo->last_eat = get_time_in_ms();
	pthread_mutex_unlock(&philo->data->m_last_eat_time);
	pthread_mutex_lock(&philo->m_times_eat);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->m_times_eat);
	usleep_functional(philo->data->tte);
	pthread_mutex_lock(&philo->data->m_last_eat_time);
	philo->last_eat = get_time_in_ms();
	pthread_mutex_unlock(&philo->data->m_last_eat_time);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	if (finish(philo))
		return ;
	print_sleep(philo);
	usleep_functional(philo->data->tts);
	if (finish(philo))
		return ;
	print_think(philo);
}
