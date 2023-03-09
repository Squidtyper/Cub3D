/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 14:24:03 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/09 14:34:07 by lizhang       ########   odam.nl         */
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
	char *newstr;

	if (!str1)
		return(str2);
	newstr = ft_strjoin(str1, str2);
	if (!newstr)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	free(str1);
	free(str2);
	return(newstr);
}