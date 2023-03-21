/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dda.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 17:29:19 by dmonfrin      #+#    #+#                 */
/*   Updated: 2023/03/17 14:19:30 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <math.h>
#include <stdio.h>

static int	st_calculate_step(double y, double x)
{
	int	step;

	if (fabs(x) > fabs(y) && x != 0)
		step = x;
	else
		step = y;
	if (step < 0)
		step *= -1;
	return (step);
}

static void	st_new_increase(double *y, double *x, int step)
{
	*y /= step;
	*x /= step;
}

void	draw_ray(t_exe_info *img, t_print_info *info)
{
	double	x_increas;
	double	y_increas;
	int		step;

	x_increas = info->start_x - info->end_x;
	y_increas = info->start_y - info->end_y;
	step = st_calculate_step(y_increas, x_increas);
	if (step == 0)
		return ;
	st_new_increase(&y_increas, &x_increas, step);
	while (step--)
	{
		info->start_x -= x_increas;
		info->start_y -= y_increas;
		mlx_put_pixel(info->img, round(info->start_x) + img->pad_x,
			round(info->start_y) + img->pad_y, info->color);
	}
}

void	draw_player_direction(t_exe_info *img)
{
	double	y_increas;
	double	x_increas;
	double	print_x;
	double	print_y;
	int		step;

	if (img->pad_x == HEIGHT_WIDTH)
		return ;
	print_x = img->player.x;
	print_y = img->player.y;
	x_increas = img->player.delta_x * 1;
	y_increas = img->player.delta_y * 1;
	step = st_calculate_step(y_increas, x_increas);
	if (step == 0)
		return ;
	st_new_increase(&y_increas, &x_increas, step);
	while (step--)
	{
		print_x += x_increas;
		print_y += y_increas;
		mlx_put_pixel(img->scene, round(print_x) + img->pad_x,
			round(print_y) + img->pad_y, 0xFFeb34db);
	}
}
