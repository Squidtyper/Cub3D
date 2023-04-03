#ifndef EXECUTION_H
# define EXECUTION_H
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include "cube3D.h"
# define HEIGHT_WIDTH 512


typedef enum e_drc
{
	HORIZONTAL,
	VERTICAL,
	VERTICAL_LEFT,
	VERTICAL_RIGHT,
	HORIZONTAL_UP,
	HORIZONTAL_DOWN,
}t_drc;

typedef enum e_num
{
	FOV = 60,
}t_num;

typedef struct s_axix
{
	double	x;
	double	y;
}t_axis;
typedef struct s_player
{
	t_axis	pos;
	t_axis	delta;
	double	angle;
}t_player;
typedef struct s_ray
{
	int		max_pg_view;
	int		pg_view;
	t_axis	base;
	t_axis	offset;
	double	angle;
	double	tan;
}t_ray;

typedef struct s_wall_pos
{
	t_axis	hor;
	t_axis	ver;
	double	dist;
	t_drc	side;
}t_wall_pos;

typedef struct s_wall_coll
{
	t_axis	offset;
	int		ipx;
	int		ipx_add_xo;
	int		ipx_sub_xo;
	int		ipx_add_yo;
	int		ipx_sub_yo;
	int		ipy;
	int		ipy_add_yo;
	int		ipy_sub_yo;
	int		ipy_add_xo;
	int		ipy_sub_xo;
}t_object_seen;

typedef struct s_print_info
{
	mlx_image_t	*img;
	uint32_t	color;
	t_axis		start_point;
	t_axis		end_point;
}t_print_info;

typedef struct s_tex_var
{
	t_axis	base;
	t_axis	offset;
	t_axis	step;
	t_drc	wall_side;
	double	line_h;
	double	ray;
}t_tex_var;

typedef struct s_exe_info
{
	mlx_t		*mlx;
	mlx_image_t	*background;
	mlx_image_t	*scene;
	t_player	player;
	t_input		*map_input;
	t_axis		pad;
	double		size;
}t_exe_info;

/* draw_dda.c*/
void			draw_ray(t_exe_info *img, t_print_info *info);
void			draw_player_direction(t_exe_info *img);
/* draw_main.c*/
int				draw_cube(t_exe_info *img);
/* draw_map.c */
void			draw_map(t_exe_info *img);
/* draw_scene_utils.c */
uint32_t		calc_color(mlx_texture_t *texture, t_tex_var *tex);
bool			is_mini_map_space(t_exe_info *img, int y, int x);
void			set_right_ray(t_wall_pos *wall, t_tex_var *tex);
/* draw_scene.c */
void			draw_ray_scene(t_exe_info *img);
/* execution_init.c */
int				init_info(t_exe_info *info);
/* execution_utils.c */
bool			is_wall(char c);
void			draw_background(t_exe_info *img);
/* keystroke_calc.c*/
void			hook(void *param);
/* keystroke.c*/
void			key_w(t_exe_info *img, t_object_seen *set);
void			key_s(t_exe_info *img, t_object_seen *set);
void			key_a(t_exe_info *img, t_object_seen *set);
void			key_d(t_exe_info *img, t_object_seen *set);
/* rays_calc.c*/
void			find_vert_wall(t_exe_info *img, t_wall_pos *w_pos, double angle);
void			find_horiz_wall(t_exe_info *img, t_wall_pos *w_pos, double angle);
/* rays_utils.c*/
void			set_print(t_exe_info *img, t_print_info *info,
					t_wall_pos *w_pos);
void			angle_normalizer(double *angle);
double			dist_pg_rayend(t_axis a, t_axis b);
t_drc			set_direction(t_drc pos, double angle);
int				calc_max_wall_dist(t_exe_info *img);

#endif
