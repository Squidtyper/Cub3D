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

#include "execution.h"
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
	int	position;

	position = round(tex->base.y) * texture->width + tex->base.x;
	position *= texture->bytes_per_pixel;
	r = texture->pixels[position];
	g = texture->pixels[position + 1];
	b = texture->pixels[position + 2];
	a = texture->pixels[position + 3];
	return (st_get_rgba(r, g, b, a));
}

bool	is_mini_map_space(t_exe_info *img, int y, int x)
{
	if (y >= img->pad.y && x >= img->pad.x)
		return (true);
	return (false);
}

void	set_right_ray(t_wall_pos *wall, t_tex_var *tex)
{
	if (wall->side == VERTICAL_LEFT || wall->side == VERTICAL_RIGHT)
		tex->ray = wall->ver.y;
	else
		tex->ray = wall->hor.x;
}
