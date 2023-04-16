/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 14:24:03 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/17 16:01:41 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
		mallocerr();
		exit(EXIT_FAILURE);
	}
	free(str1);
	free(str2);
	return (newstr);
}

bool	only_digits(char *str)
{
	int		i;
	int		n_digit;
	char	*str2;

	i = 0;
	n_digit = 0;
	if (!str)
		return (false);
	str2 = clear_str_space(str);
	while (str2[i])
	{
		if (ft_isdigit(str2[i]) == 0)
			return (0);
		if (ft_isdigit(str2[i]) == 1)
			n_digit++;
		i++;
	}
	free(str2);
	if (n_digit == 0)
		return (false);
	return (true);
}

char	*clear_str_space(char *str)
{
	int		i;
	int		i2;
	char	*str2;

	i = 0;
	if (!str)
		return (NULL);
	i2 = ft_strlen(str) - 1;
	while (str[i] == 32 || str[i] == 9 || str[i] == 13)
		i++;
	while (str[i2] == 32 || str[i2] == 9 || str[i2] == 13)
		i2--;
	str2 = ft_substr(str, i, i2 - i + 1);
	return (str2);
}

char	*rm_vertical_tab(char *str)
{
	int		i;
	char	*str2;

	if (!str)
		return (NULL);
	i = ft_strlen(str) - 1;
	if (str[i] == 13)
		i--;
	str2 = ft_substr(str, 0, i + 1);
	free(str);
	return (str2);
}
