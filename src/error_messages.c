/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_messages.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 16:37:54 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/17 16:00:33 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"
#include <errno.h>
#include <stdio.h>

void	ac_error(int ac)
{
	if (ac != 2)
	{
		ft_putstr_fd("please use 1 argument (map filename)\n", STDERR_FILENO);
		exit(1);
	}
}

void	mallocerr(void)
{
	perror("");
	exit(EXIT_FAILURE);
}

int	color_atoi(char *str)
{
	int	i;
	int	color;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) != 1)
		{
			printf("Unexpected character found in color specification\n");
			exit(1);
		}
		i++;
	}
	color = ft_atoi(str);
	if (color < 0 || color > 255)
	{
		printf("Error: rgb color cannot exceed 0 - 255");
		exit(1);
	}
	return (color);
}
