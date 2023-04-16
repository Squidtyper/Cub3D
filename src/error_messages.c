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

#include "parsing.h"
#include <errno.h>

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
	write(1, "Malloc failed\n", 14);
}

int	color_atoi(char *str, t_check *check)
{
	int		i;
	char	*str2;
	int		color;

	i = 0;
	str2 = clear_str_space(str);
	while (str2[i])
	{
		if (ft_isdigit(str2[i]) != 1)
		{
			printf("Unexpected character found in color specification\n");
			parsing_clean(check);
		}
		i++;
	}
	color = ft_atoi(str2);
	free(str2);
	if (color < 0 || color > 255)
	{
		printf("Error: rgb color cannot exceed 0 - 255");
		parsing_clean(check);
	}
	return (color);
}
