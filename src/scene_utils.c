/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scene_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 12:15:32 by dmonfrin      #+#    #+#                 */
/*   Updated: 2023/03/17 18:40:21 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"
#include <math.h>

static uint32_t	st_get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t	calc_color(mlx_texture_t *texture, t_tex_var *tex)
{
	int	r;
	int	g;
	int	b;
	int	a;
	int position;

	position = round(tex->y) * texture->width + tex->x;
	position *= texture->bytes_per_pixel;
	r = texture->pixels[position];
	g = texture->pixels[position + 1];
	b = texture->pixels[position + 2];
	a = texture->pixels[position + 3];
	if (tex->wall_type == DOOR_OPEN)
		return(st_get_rgba(r, g, b, 150));
	return (st_get_rgba(r, g, b, a));
}

mlx_texture_t	*calculate_texture(t_image_mlx *img, t_tex_var *tex)
{
	if (tex->wall_type != WALL)
		return (img->map_input->door);
	if (tex->wall_side == VERTICAL_LEFT)
		return (img->map_input->EA_tex);
	else if (tex->wall_side == VERTICAL_RIGHT)
		return (img->map_input->WE_tex);
	else if (tex->wall_side == HORIZONTAL_UP)
		return (img->map_input->NO_tex);
	else
		return (img->map_input->SO_tex);
}

bool	is_mini_map_space(t_image_mlx *img, int y, int x)
{
	if (y >= img->pad_y && x >= img->pad_x)
		return (true);
	return (false);
}

void	set_right_ray(t_image_mlx *img, t_wall_pos *wall, t_tex_var *tex)
{
	if (wall->side == VERTICAL_LEFT || wall->side == VERTICAL_RIGHT)
	{	
		tex->ray = wall->ver_y;
		set_is_door(img, wall, wall->ver_x, wall->ver_y);
	}
	else
	{	
		tex->ray = wall->hor_x;
		set_is_door(img, wall, wall->hor_x, wall->hor_y);
	}
}
