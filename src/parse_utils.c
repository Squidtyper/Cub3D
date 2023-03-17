/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 14:24:03 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/14 18:42:40 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	cleardarray(char **array)
{
	int	count;

	count = 0;
	if (!array || array == NULL)
		return ;
	while (array[count])
	{
		free(array[count]);
		count++;
	}
	if (array)
		free(array);
}

char	*join_free(char *str1, char *str2)
{
	char	*newstr;

	if (!str1)
		return (str2);
	newstr = ft_strjoin(str1, str2);
	if (!newstr)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	free(str1);
	free(str2);
	return (newstr);
}

int	only_digits(char *str)
{
	int	i;
	int	n_digit;

	i = 0;
	n_digit = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '	' && ft_isdigit(str[i]) == 0)
			return (0);
		if (ft_isdigit(str[i]) == 1)
			n_digit++;
		i++;
	}
	if (n_digit == 0)
		return (0);
	return (1);
}
