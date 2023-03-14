#include "cube3D.h"

void	draw_square(t_print_info *info)
{
	uint32_t	x_i;

	while (info->start_y + 1 < info->end_y - 1)
	{
		x_i = info->start_x + 1;
		while (x_i < info->end_x -1)
		{
			mlx_put_pixel(info->img, x_i, info->start_y + 1, info->color);
			x_i++;
		}
		info->start_y++;
	}
}

void	calculate_map_size(t_image_mlx *img)
{
	img->blk_size = HEIGHT_WIDTH / 6;
	while (img->blk_size * img->map_input->map_width > HEIGHT_WIDTH / 6)
		img->blk_size--;
	while (img->blk_size * img->map_input->map_height > HEIGHT_WIDTH / 6)
		img->blk_size--;
	img->pad_x = HEIGHT_WIDTH - img->map_input->map_width * img->blk_size;
	img->pad_y = HEIGHT_WIDTH - img->map_input->map_height * img->blk_size;
	if (img->blk_size < 16)
	{	
		img->blk_size = 16;
		img->pad_x = HEIGHT_WIDTH;
		img->pad_y = HEIGHT_WIDTH;
	}
}

void	set_info(t_print_info *info, t_image_mlx *img, int y, int x)
{
	info->start_y = y * img->blk_size + img->pad_y;
	info->start_x = x * img->blk_size + img->pad_x;
	info->end_y = (y + 1) * img->blk_size + img->pad_y;
	info->end_x = (x + 1) * img->blk_size + img->pad_x;
	info->img = img->map;
}

void	draw_map(t_image_mlx *img)
{
	unsigned int	y;
	unsigned int	x;
	t_print_info	info;

	calculate_map_size(img);
	if(img->pad_x == HEIGHT_WIDTH)
		return ;
	y = 0;
	while (y < img->map_input->map_height)
	{
		x = 0;
		while (x < img->map_input->map_width)
		{
			if(img->map_input->map_points[y][x]  == '1')
				info.color = 0xFFFFFFFF;
			else
				info.color =  0x000000FF;
			set_info(&info, img, y, x);
			draw_square(&info);
			x++;
		}
		y++;
	}
}
