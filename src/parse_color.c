/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_color.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 17:52:53 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/17 16:03:00 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*combine_lines(char **words)
{
	int		i;
	char	*comb;

	i = 1;
	if (words[i + 1])
	{
		while (words[i + 1])
		{
			comb = ft_strjoin(words[i], words[i + 1]);
			i++;
		}
	}
	else
		comb = ft_strdup(words[1]);
	return (comb);
}

void	color_fill(char **colors, char *colorline, char **lines, t_check *check)
{
	int		i;
	int		i2;
	int		i3;

	i = 0;
	i2 = 0;
	i3 = 0;
	while (colorline[i] && i3 < 3)
	{
		if (ft_isdigit(colorline[i]) != 1)
		{
			free(colorline);
			cleardarray(lines);
			color_incorrect(check);
		}
		i2 = i;
		while (ft_isdigit(colorline[i2]) == 1)
			i2++;
		colors[i3] = ft_substr(colorline, i, i2 - i);
		i = i2;
		if (colorline[i] == ',')
			i++;
		i3++;
	}
	colors[3] = NULL;
}

char	**color_check(char **words, char **lines, t_check *check)
{
	char	*colorline;
	char	**colors;

	colors = (char **)malloc(sizeof(char *) * 4);
	if (!colors)
	{
		mallocerr();
		cleardarray(lines);
		parsing_clean(check);
	}
	colorline = combine_lines(words);
	color_fill(colors, colorline, lines, check);
	free(colorline);
	return (colors);
}

void	find_color(t_check *check, char **lines)
{
	char	**words;
	char	**colors;
	int		i;

	i = 0;
	while (lines[i])
	{
		if (ft_strlen(lines[i]) > 2)
		{
			words = ft_space_split(lines[i]);
			if (!words)
			{
				mallocerr();
				parsing_clean(check);
			}
			if ((ft_strncmp(words[0], "F", 2) == 0 || \
			ft_strncmp(words[0], "C", 2) == 0) && words[1])
			{
				colors = color_check(words, lines, check);
				parse_color(words[0], colors, check);
			}
			cleardarray(words);
		}
		i++;
	}
}
