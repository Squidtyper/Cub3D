#include "cube3D.h"

static uint32_t st_get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t calc_color(mlx_texture_t *texture, int position)
{
	int	r;
	int	g;
	int	b;
	int	a;

	position *= texture->bytes_per_pixel;
	r = texture->pixels[position];
	g = texture->pixels[position + 1];
	b = texture->pixels[position + 2];
	a = texture->pixels[position + 3];
	return (st_get_rgba(r, g, b, a));

}

mlx_texture_t	*calculate_texture(t_image_mlx *img, t_tex_var *tex)
{
	if (tex->wall == VERTICAL_LEFT)
		return ( img->map_input->EA_tex);
	else if (tex->wall == VERTICAL_RIGHT)
		return (img->map_input->WE_tex);
	else if (tex->wall == HORIZONTAL_UP)
		return (img->map_input->NO_tex);
	else
		return (img->map_input->SO_tex);
}

double	calculate_x(t_image_mlx *img, mlx_texture_t *text, t_tex_var *tex)
{
	double	x;

	if (img->blk_size > text->width) 
		x = (int)(tex->ray / (img->blk_size / text->width)) % text->width;
	else
		x = (int)(tex->ray * (text->width / img->blk_size)) % text->width;
	if (tex->wall == HORIZONTAL_DOWN || tex->wall == VERTICAL_LEFT)
		x = text->width - 1 - x;
	return (x);
}

void	set_ray(t_ray_end *rays, t_tex_var *tex)
{
	if (rays->pos == VERTICAL_LEFT || rays->pos == VERTICAL_RIGHT)
		tex->ray = rays->ver_y;
	else
		tex->ray = rays->hor_x;
}