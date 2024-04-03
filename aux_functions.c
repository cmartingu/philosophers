/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <carlos-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:43:10 by carlos-m          #+#    #+#             */
/*   Updated: 2024/04/01 16:43:11 by carlos-m         ###   ########.fr       */
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