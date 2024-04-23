/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:10:54 by carlos-m          #+#    #+#             */
/*   Updated: 2024/04/07 12:10:56 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*principal(t_philo	*filo)
{
	while (1)
	{
		pthread_mutex_lock(&filo->data->m_dead);
		if (filo->data->one_dead == 1)
		{
			pthread_mutex_unlock(&filo->data->m_dead);
			return (NULL);
		}
		pthread_mutex_unlock(&filo->data->m_dead);
		print_message(filo->filo_id, "is thinking", &filo->data->m_write);
		usleep(filo->data->tts * 1000);
		pthread_mutex_lock(&filo->data->m_dead);
		if (filo->data->one_dead == 1)
		{
			pthread_mutex_unlock(&filo->data->m_dead);
			return (NULL);
		}
		pthread_mutex_unlock(&filo->data->m_dead);
		if (filo->last_eat != 0)
		{
			if (get_time_in_ms() - filo->last_eat > filo->data->ttd)
			{
				pthread_mutex_lock(&filo->data->m_dead);
				filo->data->one_dead = 1;
				print_message(filo->filo_id, "died", &filo->data->m_write);
				pthread_mutex_unlock(&filo->data->m_dead);
				return (NULL);
			}
		}
		if (filo->filo_id == 0 || filo->filo_id % 2 == 0)
		{
			pthread_mutex_lock(filo->r_fork);
			pthread_mutex_lock(&filo->data->m_dead);
			if (filo->data->one_dead == 1)
			{
				pthread_mutex_unlock(filo->r_fork);
				pthread_mutex_unlock(&filo->data->m_dead);
				return (NULL);
			}
			pthread_mutex_unlock(&filo->data->m_dead);
			print_message(filo->filo_id, "has taken a fork", &filo->data->m_write);
			pthread_mutex_lock(filo->l_fork);
			pthread_mutex_lock(&filo->data->m_dead);
			if (filo->data->one_dead == 1)
			{
				pthread_mutex_unlock(filo->r_fork);
				pthread_mutex_unlock(filo->l_fork);
				pthread_mutex_unlock(&filo->data->m_dead);
				return (NULL);
			}
			pthread_mutex_unlock(&filo->data->m_dead);
			print_message(filo->filo_id, "has taken a fork", &filo->data->m_write);
		}
		else
		{
			pthread_mutex_lock(filo->l_fork);
			pthread_mutex_lock(&filo->data->m_dead);
			if (filo->data->one_dead == 1)
			{
				pthread_mutex_unlock(filo->l_fork);
				pthread_mutex_unlock(&filo->data->m_dead);
				return (NULL);
			}
			pthread_mutex_unlock(&filo->data->m_dead);
			print_message(filo->filo_id, "has taken a fork", &filo->data->m_write);
			pthread_mutex_lock(filo->r_fork);
			pthread_mutex_lock(&filo->data->m_dead);
			if (filo->data->one_dead == 1)
			{
				pthread_mutex_unlock(filo->l_fork);
				pthread_mutex_unlock(filo->r_fork);
				pthread_mutex_unlock(&filo->data->m_dead);
				return (NULL);
			}
			pthread_mutex_unlock(&filo->data->m_dead);
			print_message(filo->filo_id, "has taken a fork", &filo->data->m_write);
		}
		pthread_mutex_lock(&filo->data->m_dead);
		if (filo->data->one_dead == 1)
		{
			pthread_mutex_unlock(filo->l_fork);
			pthread_mutex_unlock(filo->r_fork);
			pthread_mutex_unlock(&filo->data->m_dead);
			return (NULL);
		}
		pthread_mutex_unlock(&filo->data->m_dead);
		print_message(filo->filo_id, "is eating", &filo->data->m_write);
		usleep(filo->data->tte * 1000);
		filo->last_eat = get_time_in_ms();
		pthread_mutex_unlock(filo->r_fork);
		pthread_mutex_unlock(filo->l_fork);
		pthread_mutex_lock(&filo->data->m_dead);
		if (filo->data->one_dead == 1)
		{
			pthread_mutex_unlock(&filo->data->m_dead);
			return (NULL);
		}
		pthread_mutex_unlock(&filo->data->m_dead);
		print_message(filo->filo_id, "is sleeping", &filo->data->m_write);
		usleep(filo->data->tts * 1000);
	}
	return (NULL);
}

void	*hilo_aux(t_general *general)
{
	int	i;

	while (1)
	{
		usleep(100);
		pthread_mutex_lock(&general->data->m_dead);
		if (general->data->one_dead == 1)
		{
			i = 0;
			while (i < general->data->filo_quant)
			{
				pthread_detach(general->hilos[i]);
				i++;
			}
			return (NULL);
		}
		pthread_mutex_unlock(&general->data->m_dead);
	}
}	

int	main(int argc, char *argv[])
{
	t_general	*general;
	int			i;

	if (argc < 5 || argc > 6)
	{
		printf("Error, invalid arguments\n");
		return (1);
	}
	general = malloc(sizeof(t_general));
	general->data = parse_args(argc, argv);
	if (!general->data)
	{
		free(general);
		return (-1);
	}
	general->hilos = malloc(general->data->filo_quant);
	if (!general->hilos)
	{
		printf("Error, malloc error\n");
		return (-1);
	}
	general->forks = malloc(general->data->filo_quant * sizeof(pthread_mutex_t));
	if (!general->forks)
	{
		printf("Error, malloc error\n");
		return (-1);
	}
	i = 0;
	while (i < general->data->filo_quant)
	{
		pthread_mutex_init(&(general->forks[i]), NULL);
		i++;
	}
	general->philosophers = malloc(general->data->filo_quant * sizeof(t_philo *));
	if (!general->philosophers)
	{
		printf("Error, malloc error\n");
		return (-1);
	}
	i = 0;
	while (i < general->data->filo_quant)
	{
		general->philosophers[i] = *ini_filo(general, i);
		pthread_create(&(general->hilos[i]), NULL, (void *)principal, (void *)(&(general->philosophers[i])));
		i++;
	}
	pthread_create(&(general->count), NULL, (void *)hilo_aux, (void *)(&general));
	pthread_join(general->count, NULL);
	i = 0;
	while (i < general->data->filo_quant)
	{
		pthread_join(general->hilos[i], NULL);
		i++;
	}
	//i = 0;
	//while (i < general->data->filo_quant)
	//{
	//	pthread_mutex_destroy(&(general->forks[i]));
	//	i++;
	//}
	//FALTAN MUTEX POR DESTRUIR(todos menos forks)
	return (0);
}
