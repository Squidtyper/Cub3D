#ifndef CUBE3D_H
# define CUBE3D_H
# include "MLX42/include/MLX42/MLX42.h"
# include <stddef.h>
// # include "libft/libft.h"
# define PI 3.1415926535
# define P2 PI/2
# define P3 3*PI/2
# define DR 0.0174533 //one degree in radians

extern uint32_t	mappa [];

extern size_t map_x;
extern size_t map_y;

typedef struct s_rays
{
	int map_x;
	int map_y;
	int map_pos;
	int dof;
	double x;
	double y;
	double a_tan;
	double x_offset;
	double y_offset;
} t_rays;


typedef struct s_ray_end
{
	double	hor_x;
	double	hor_y;
	double	ver_x;
	double	ver_y;
	double	dist;
	int		pos;
} t_ray_end;

typedef struct s_player
{
	mlx_image_t	*img;
	double x;
	double y;
	double delta_x;
	double delta_y;
	double angle;
}	t_player;

typedef struct s_print_info
{
	mlx_image_t	*img;
	double start_x;
	double start_y;
	double end_x;
	double end_y;
	uint32_t color;
}	t_print_info;


typedef struct s_image_mlx
{
	mlx_t		*mlx;
	mlx_image_t	*map;
	t_player	player;
}	t_image_mlx;

void	draw_line(t_player *player);
void	draw_lineray(t_print_info *info);
void	draw_rays_2D (t_player *player);
void	draw3d(t_print_info *info);
void	scene3d(t_ray_end *rays, int ray, double angle, t_player *player);

void	key_w(t_image_mlx *img);
void	key_s(t_image_mlx *img);
void	key_a(t_image_mlx *img);
void	key_d(t_image_mlx *img);
void	key_left(t_image_mlx *img);
void	key_right(t_image_mlx *img);

#endif
