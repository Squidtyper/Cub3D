/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 12:20:11 by dmonfrin      #+#    #+#                 */
/*   Updated: 2023/03/17 15:51:43 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	st_draw_square(t_print_info *value)
{
	uint32_t	x_i;

	while (value->start_point.y < value->end_point.y - 1)
	{
		x_i = value->start_point.x + 1;
		while (x_i < value->end_point.x -1)
		{
			mlx_put_pixel(value->img, x_i, value->start_point.y, value->color);
			x_i++;
		}
		value->start_point.y++;
	}
}

static void	st_set_info(t_print_info *value, t_exe_info *info, int y, int x)
{
	value->start_point.y = y * info->size + info->pad.y;
	value->start_point.x = x * info->size + info->pad.x;
	value->end_point.y = (y + 1) * info->size + info->pad.y;
	value->end_point.x = (x + 1) * info->size + info->pad.x;
	value->img = info->background;
}

void	draw_map(t_exe_info *info)
{
	unsigned int	y;
	unsigned int	x;
	t_print_info	value;

	if (info->pad.x == HEIGHT_WIDTH)
		return ;
	y = 0;
	while (y < info->map_input->map_height)
	{
		x = 0;
		while (x < info->map_input->map_width)
		{
			if (is_wall(info->map_input->map_points[y][x]))
				value.color = 0xFFFFFFFF;
			else
				value.color = 0x000000FF;
			st_set_info(&value, info, y, x);
			st_draw_square(&value);
			x++;
		}
		y++;
	}
}
