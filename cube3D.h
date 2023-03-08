#ifndef CUBE3D_H
# define CUBE3D_H
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# define PI 3.1415926535
# define P2 PI/2
# define P3 3*PI/2

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
	double angle;
	double a_tan;
	double x_offset;
	double y_offset;
} t_rays;


typedef struct s_ray_end_point
{
	double hor_x;
	double hor_y;
	double ver_x;
	double ver_y;
} t_ray_end_point;

typedef struct s_player
{
	mlx_image_t	*img;
	double x;
	double y;
	double delta_x;
	double delta_y;
	double angle;
}	t_player;


typedef struct s_image_mlx
{
	mlx_t		*mlx;
	mlx_image_t	*map;
	t_player	player;
}	t_image_mlx;

void	draw_line(t_player *player);
void	draw_lineray(t_player *player, double end_x, double end_y);
void	draw_rays_2D (t_player *player);

void	key_w(t_image_mlx *img);
void	key_s(t_image_mlx *img);
void	key_a(t_image_mlx *img);
void	key_d(t_image_mlx *img);
void	key_left(t_image_mlx *img);
void	key_right(t_image_mlx *img);

#endif
