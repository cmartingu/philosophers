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

int	control_finish(t_general *general)
{
	size_t	time;
	int		i;

	i = 0;
	while (i < general->data->num_philo)
	{
		pthread_mutex_lock(&general->data->m_last_eat_time);
		if (get_time_in_ms() - general->philos[i].last_eat >= \
		general->data->ttd)
		{
			pthread_mutex_lock(&general->philos->data->m_write);
			time = get_time_in_ms();
			if (finish(&(general->philos[i])))
			{
				pthread_mutex_unlock(&general->philos->data->m_write);
				pthread_mutex_unlock(&general->data->m_last_eat_time);
				return (1);
			}
			printf("%lu %d died\n", time, i);
			pthread_mutex_unlock(&general->data->m_write);
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

void	eat_loop(t_philo *philo)
{
	size_t	time;

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
	pthread_mutex_lock(&philo->data->m_write);
	time = get_time_in_ms();
	if (finish(philo))
	{
		pthread_mutex_unlock(&philo->data->m_write);
		return ;
	}
	printf("%lu %d has taken a fork\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->m_write);
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
	pthread_mutex_lock(&philo->data->m_write);
	time = get_time_in_ms();
	if (finish(philo))
	{
		pthread_mutex_unlock(&philo->data->m_write);
		return ;
	}
	printf("%lu %d has taken a fork\n", time, philo->id);
	printf("%lu %d is eating\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->m_write);
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
	pthread_mutex_lock(&philo->data->m_write);
	time = get_time_in_ms();
	if (finish(philo))
	{
		pthread_mutex_unlock(&philo->data->m_write);
		return ;
	}
	printf("%lu %d is sleeping\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->m_write);
	time = get_time_in_ms();
	while (get_time_in_ms() - time < philo->data->tts)
		usleep(250);
	if (finish(philo))
		return ;
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
	size_t	time;
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
	pthread_mutex_lock(&philo->data->m_write);
	time = get_time_in_ms();
	if (finish(philo))
	{
		pthread_mutex_unlock(&philo->data->m_write);
		return (NULL);
	}
	printf("%lu %d is thinking\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->m_write);
	while (1)
	{
		if (finish(philo))
			break ;
		eat_loop(philo);
	}
	return (NULL);
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

int	main(int argc, char *argv[])
{
	t_general	general;

	if (argc < 5 || argc > 6)
	{
		printf("Error, remember to set 5 or 6 arguments\n");
		return (1);
	}
	if (parse_args(argv) == 1)
	{
		printf("Error, remember to set only positive numbers\n");
		return (1);
	}
	ini_general(&general, argv, argc);
	start_program(&general);
	ft_free(&general);
	return (0);
}
