/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_scene.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/15 18:22:24 by dmonfrin      #+#    #+#                 */
/*   Updated: 2023/03/16 19:32:52 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"
#include <math.h>
#define PI 3.1415926535

void	st_draw_wall(t_image_mlx *img, double start_x, double start_y,
	t_tex_var *tex)
{
	int				y;
	int				color;
	mlx_texture_t	*texture;

	texture = calculate_texture(img, tex);
	tex->step_y = texture->height / tex->step_y;
	tex->y = tex->y_offset * tex->step_y;
	tex->x = calculate_x(img, texture, tex);
	y = 0;
	while (y < tex->line_h)
	{
		color = calc_color(texture, round(tex->y) * texture->width + tex->x);
		mlx_put_pixel(img->player.img, start_x, y + start_y, color);
		y++;
		if (round(tex->y + tex->step_y) * texture->width + tex->x < texture->width * texture->height )
			tex->y += tex->step_y;

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
void	draw_scene(t_image_mlx *img, t_wall_pos *wall, int ray, double angle)
{
	double		line_h;
	double		line_offset;
	t_tex_var	texture;

	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	wall->dist = wall->dist * cos(angle);
	line_h = (img->blk_size * (HEIGHT_WIDTH / 1.5)) / wall->dist;
	texture.step_y = line_h;
	texture.y_offset = 0;
	if (line_h > HEIGHT_WIDTH / 1.5)
	{	
		texture.y_offset = (line_h - HEIGHT_WIDTH / 1.5) / 2.0;
		line_h = HEIGHT_WIDTH / 1.5;
	}
	line_offset = HEIGHT_WIDTH / 2 - ((int)line_h >> 1);
	texture.line_h = line_h;
	set_right_ray(wall, &texture);
	texture.wall_side = wall->side;
	st_draw_wall(img, ray, line_offset + 30, &texture);
}
