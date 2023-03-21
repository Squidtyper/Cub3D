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

#include "cube3D.h"
#include <math.h>
#include <stdio.h>

void	color_double(bool testvalue)
{
	if (testvalue == true)
	{
		printf("Error: double values for ceiling color or floor color found\n");
		exit(1);
	}
}

long long	color_combine(char *r, char *b, char *g)
{
	int			rclr;
	int			gclr;
	int			bclr;
	long long	combined;

	rclr = color_atoi(r);
	gclr = color_atoi(g);
	bclr = color_atoi(b);
	combined = rclr * pow(2, 24) + gclr * pow(2, 16) + bclr * pow(2, 8) + 255;
	return (combined);
}

void	parse_color(char **words, t_input *input)
{
	char		**frag;

	frag = ft_space_split(words[0]);
	if (!frag)
		mallocerr();
	if ((frag[1] && only_digits(frag[1]) == 0) || !frag[1] || \
	only_digits(words[1]) == 0 || only_digits(words[2]) == 0)
	{
		printf("Error: color codes not correct\n");
		exit(1);
	}
	if (ft_strncmp(frag[0], "C", 2) == 0)
	{
		color_double(input->c_found);
		input->c_color = color_combine(frag[1], words[1], words[2]);
		input->c_found = true;
	}
	if (ft_strncmp(frag[0], "F", 2) == 0)
	{
		color_double(input->f_found);
		input->f_color = color_combine(frag[1], words[1], words[2]);
		input->f_found = true;
	}
	cleardarray(frag);
}

void	find_color(t_input *input)
{
	char	**words;
	int		i;
	int		i2;

	i = 0;
	input->lines = ft_split(input->file_content, '\n');
	while (input->lines[i])
	{
		words = ft_split(input->lines[i], ',');
		if (!words)
			mallocerr();
		i2 = 0;
		while (words[i2])
			i2++;
		if (i2 == 3)
			parse_color(words, input);
		i++;
		cleardarray(words);
	}
}
