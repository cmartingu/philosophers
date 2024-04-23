/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:09:05 by carlos-m          #+#    #+#             */
/*   Updated: 2024/04/16 13:09:06 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec) *1000 + (long long)(tv.tv_usec) / 1000);
}

void	print_message(int i, char *msg, pthread_mutex_t *escr)
{
	pthread_mutex_lock(escr);
	printf("%lld %d %s\n", get_time_in_ms(), i, msg);
	pthread_mutex_unlock(escr);
}