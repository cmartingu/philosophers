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
