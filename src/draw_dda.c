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

static int	st_calculate_step(t_axis ax)
{
	int	step;

	if (fabs(ax.x) > fabs(ax.y) && ax.x != 0)
		step = ax.x;
	else
		step = ax.y;
	if (step < 0)
		step *= -1;
	return (step);
}

static void	st_new_increase(t_axis *ax, int step)
{
	ax->y /= step;
	ax->x /= step;
}

void	draw_ray(t_exe_info *img, t_print_info *info)
{
	t_axis	increase;
	int		step;

	increase.x = info->start_point.x - info->end_point.x;
	increase.y = info->start_point.y - info->end_point.y;
	step = st_calculate_step(increase);
	if (step == 0)
		return ;
	st_new_increase(&increase, step);
	while (step--)
	{
		info->start_point.x -= increase.x;
		info->start_point.y -= increase.y;
		mlx_put_pixel(info->img, round(info->start_point.x) + img->pad.x,
			round(info->start_point.y) + img->pad.y, info->color);
	}
}

void	draw_player_direction(t_exe_info *img)
{
	t_axis	increase;
	t_axis	print;
	int		step;

	if (img->pad.x == HEIGHT_WIDTH)
		return ;
	print.x = img->player.pos.x;
	print.y = img->player.pos.y;
	increase.x = img->player.delta.x * 1;
	increase.y = img->player.delta.y * 1;
	step = st_calculate_step(increase);
	if (step == 0)
		return ;
	st_new_increase(&increase, step);
	while (step--)
	{
		print.x += increase.x;
		print.y += increase.y;
		mlx_put_pixel(img->scene, round(print.x) + img->pad.x,
			round(print.y) + img->pad.y, 0xFFeb34db);
	}
}
