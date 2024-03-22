/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:39:10 by carlos-m          #+#    #+#             */
/*   Updated: 2024/03/22 12:39:11 by carlos-m         ###   ########.fr       */
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

t_philo	*parse_args(int argc, char *argv[])
{
	t_philo	*filo;

	if (argc < 5 || argc > 6)
		return (NULL);
	filo = malloc(sizeof(t_philo));
	filo->num_philo = ft_atoi(argv[1]);
	filo->ttd = ft_atoi(argv[2]);
	filo->tte = ft_atoi(argv[3]);
	filo->tts = ft_atoi(argv[4]);
	if (argc == 6)
	{
		filo->must_eat = ft_atoi(argv[5]);
		if (filo->must_eat <= 0)
			return (free(filo), NULL);
	}
	else
		filo->must_eat = 0;
	if (filo->num_philo <= 0 || filo->ttd <= 0 || \
	filo->tte <= 0 || filo->tts <= 0)
		return (free(filo), NULL);
	filo->dead = 0;
	return (filo);
}
