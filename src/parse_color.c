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
#include <math.h>

void	color_double(bool testvalue, t_check *check)
{
	if (testvalue == true)
	{
		printf("Error: double values for ceiling color or floor color found\n");
		parsing_clean(check);
	}
}

void	color_incorrect(t_check *check)
{
	printf("Error: color codes are not correct\n");
	parsing_clean(check);
}

long long	color_comb(char *r, char *b, char *g, t_check *check)
{
	int			rclr;
	int			gclr;
	int			bclr;
	long long	combined;

	rclr = color_atoi(r, check);
	gclr = color_atoi(g, check);
	bclr = color_atoi(b, check);
	combined = rclr * pow(2, 24) + gclr * pow(2, 16) + bclr * pow(2, 8) + 255;
	return (combined);
}

void	parse_color(char **words, t_check *check)
{
	char		**frag;

	frag = ft_space_split(words[0]);
	if (!frag)
	{
		mallocerr();
		parsing_clean(check);
	}
	if (!frag[1] || only_digits(frag[1]) == false || \
	only_digits(words[1]) == false || only_digits(words[2]) == false)
		color_incorrect(check);
	if (ft_strncmp(frag[0], "C", 2) == 0)
	{
		color_double(check->c_found, check);
		check->input->c_color = color_comb(frag[1], words[1], words[2], check);
		check->c_found = true;
	}
	if (ft_strncmp(frag[0], "F", 2) == 0)
	{
		color_double(check->f_found, check);
		check->input->f_color = color_comb(frag[1], words[1], words[2], check);
		check->f_found = true;
	}
	cleardarray(frag);
}

void	find_color(t_check *check, char **lines)
{
	char	**words;
	int		i;
	int		i2;

	i = 0;
	while (lines[i])
	{
		if (ft_strlen(lines[i]) > 0)
		{
			words = ft_split(lines[i], ',');
			if (!words)
			{
				mallocerr();
				cleardarray(lines);
				parsing_clean(check);
			}
			i2 = 0;
			while (words[i2])
				i2++;
			if (i2 == 3)
				parse_color(words, check);
			cleardarray(words);
		}
		i++;
	}
}
