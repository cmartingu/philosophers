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
