#include "execution.h"
#include <math.h>

static int	st_set_mlx(t_exe_info *info)
{
	info->mlx = mlx_init(HEIGHT_WIDTH, HEIGHT_WIDTH, "Cub3D", false);
	if (!info->mlx)
		return (EXIT_FAILURE);
	info->background = mlx_new_image(info->mlx, HEIGHT_WIDTH, HEIGHT_WIDTH);
	if (!info->background)
	{
		mlx_terminate(info->mlx);
		return (EXIT_FAILURE);
	}
	info->scene = mlx_new_image(info->mlx, HEIGHT_WIDTH, HEIGHT_WIDTH);
	if (!info->scene)
	{
		mlx_delete_image(info->mlx, info->background);
		mlx_terminate(info->mlx);
		return (EXIT_FAILURE);
	}
	return (MLX_SUCCESS);
}

static void	st_calculate_map_size(t_exe_info *info)
{
	info->blk_size = HEIGHT_WIDTH / 6;
	while (info->blk_size * info->map_input->map_width > HEIGHT_WIDTH / 6)
		info->blk_size--;
	while (info->blk_size * info->map_input->map_height > HEIGHT_WIDTH / 6)
		info->blk_size--;
	info->pad_x = HEIGHT_WIDTH - info->map_input->map_width * info->blk_size;
	info->pad_y = HEIGHT_WIDTH - info->map_input->map_height * info->blk_size;
	if (info->blk_size < 2)
	{	
		info->blk_size = 2;
		info->pad_x = HEIGHT_WIDTH;
		info->pad_y = HEIGHT_WIDTH;
	}
}

static void	st_set_player(t_exe_info *info)
{
	t_input	*p;

	p = info->map_input;
	info->player.angle = p->a_player;
	info->player.x = p->player_x * info->blk_size + info->blk_size / 2;
	info->player.y = p->player_y * info->blk_size + info->blk_size / 2;
	info->player.delta_x = cos(info->player.angle) * (info->blk_size / 30);
	info->player.delta_y = sin(info->player.angle) * (info->blk_size / 30);
}

static int	st_init_info(t_exe_info	*info)
{
	st_calculate_map_size(info);
	st_set_player(info);
	return (st_set_mlx(info));
}

void	execution(t_input	*input)
{
	t_exe_info	info;

	info.map_input = input;
	if (st_init_info(&info) == EXIT_FAILURE)
		return ;
	draw_background(&info);
	if (draw_cube(&info) == EXIT_FAILURE)
		mlx_close_window(info.mlx);
	mlx_loop_hook(info.mlx, &hook, &info);
	mlx_loop(info.mlx);
	mlx_delete_image(info.mlx, info.scene);
	mlx_delete_image(info.mlx, info.background);
	mlx_terminate(info.mlx);
}
