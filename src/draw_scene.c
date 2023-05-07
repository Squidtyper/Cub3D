/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_scene.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/15 18:22:24 by dmonfrin      #+#    #+#                 */
/*   Updated: 2023/03/17 18:39:35 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <math.h>

double	st_calculate_x(t_exe_info *info, mlx_texture_t *text,
	t_tex_var *tex)
{
	int	x;

	if (info->size > text->width)
		x = (int)(tex->ray / (info->size / text->width)) % (int)text->width;
	else
		x = (int)(tex->ray * (text->width / info->size)) % (int)text->width;
	if (tex->wall_side == HORIZONTAL_UP || tex->wall_side == VERTICAL_LEFT)
		x = (int)text->width - x;
	return (x);
}

static mlx_texture_t	*st_calculate_texture(t_exe_info *img, t_tex_var *tex)
{
	if (tex->wall_side == VERTICAL_RIGHT)
		return (img->map_input->textures->next->next->content);
	else if (tex->wall_side == VERTICAL_LEFT)
		return (img->map_input->textures->next->next->next->content);
	else if (tex->wall_side == HORIZONTAL_UP)
		return (img->map_input->textures->content);
	else
		return (img->map_input->textures->next->content);
}

static void	st_draw_wall(t_exe_info *info, double start_x, double start_y,
	t_tex_var *tex)
{
	int				y;
	int				color;
	mlx_texture_t	*texture;

	texture = st_calculate_texture(info, tex);
	tex->step.y = texture->height / tex->step.y;
	tex->base.y = tex->offset.y * tex->step.y;
	tex->base.x = st_calculate_x(info, texture, tex);
	y = 0;
	while (y < tex->line_h)
	{
		if (is_mini_map_space(info, y + start_y, start_x))
			return ;
		color = calc_color(texture, tex);
		mlx_put_pixel(info->scene, start_x, y + start_y, color);
		y++;
		if (round(tex->base.y + tex->step.y) * texture->width + tex->base.x
			< texture->width * texture->height)
			tex->base.y += tex->step.y;
	}
}

/*
    To draw the scene we use vertical lines
    line_h is the length of the line that gives the illusion of the distance
    line offset is just a padding of the line to have them 
    at the center of the screen.
    To avoid the fisheye effect (that happens because of different length 
    of the ray) we need to myltiply the distance of the ray with the cosine 
    of the distance of the player angle and the ray angle, all the numeric 
    values are going to be change based on the size of the screen
*/
void	draw_scene(t_exe_info *info, t_wall_pos *wall, int ray, double angle)
{
	double		line_h;
	double		line_offset;
	t_tex_var	texture;

	angle_normalizer(&angle);
	wall->dist = wall->dist * cos(angle);
	line_h = (info->size * HEIGHT_WIDTH) / wall->dist;
	texture.step.y = line_h;
	texture.offset.y = 0;
	if (line_h > HEIGHT_WIDTH)
	{	
		texture.offset.y = (line_h - HEIGHT_WIDTH) / 2.0;
		line_h = HEIGHT_WIDTH;
	}
	line_offset = (HEIGHT_WIDTH - 1) / 2.0 - ((int)(line_h - 1) >> 1);
	texture.line_h = line_h;
	set_right_ray(wall, &texture);
	texture.wall_side = wall->side;
	st_draw_wall(info, ray, line_offset, &texture);
}
