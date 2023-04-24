/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_color2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/21 22:08:47 by lizhang       #+#    #+#                 */
/*   Updated: 2023/04/23 15:22:50 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <math.h>

long long	color_comb(char *r, char *g, char *b, t_check *check)
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

void	parse_color(char *ind, char **colors, t_check *check)
{
	if (only_digits(colors[0]) == false || \
	only_digits(colors[1]) == false || only_digits(colors[2]) == false)
	{
		cleardarray(colors);
		color_incorrect(check);
	}
	if (ft_strncmp(ind, "C", 2) == 0)
	{
		color_double(check->c_found, check);
		check->input->c_color = color_comb(colors[0], colors[1], \
		colors[2], check);
		check->c_found = true;
	}
	if (ft_strncmp(ind, "F", 2) == 0)
	{
		color_double(check->f_found, check);
		check->input->f_color = color_comb(colors[0], colors[1], \
		colors[2], check);
		check->f_found = true;
	}
	cleardarray(colors);
}
