#ifndef BONUS
# ifndef EXECUTION_H
#  define EXECUTION_H
#  include "../MLX42/include/MLX42/MLX42.h"
#  include "../libft/libft.h"
#  include "cube3d.h"
#  define HEIGHT_WIDTH 512

typedef enum e_drc
{
	HORIZONTAL,
	VERTICAL,
	VERTICAL_LEFT,
	VERTICAL_RIGHT,
	HORIZONTAL_UP,
	HORIZONTAL_DOWN,
}	t_drc;

typedef struct s_ray
{
	int		max_pg_view;
	int		pg_view;
	double	x;
	double	y;
	double	x_offset;
	double	y_offset;
	double	tan;
	double	angle;
}	t_ray;

typedef struct s_player
{
	double		x;
	double		y;
	double		delta_x;
	double		delta_y;
	double		angle;
}	t_player;

typedef struct s_wall_pos
{
	double	hor_x;
	double	hor_y;
	double	ver_x;
	double	ver_y;
	double	dist;
	t_drc	side;
}	t_wall_pos;

typedef struct s_wall_coll
{
	int	x_offset;
	int	y_offset;
	int	ipx;
	int	ipx_add_xo;
	int	ipx_sub_xo;
	int	ipx_add_yo;
	int	ipx_sub_yo;
	int	ipy;
	int	ipy_add_yo;
	int	ipy_sub_yo;
	int	ipy_add_xo;
	int	ipy_sub_xo;
}	t_wall_coll;

typedef struct s_print_info
{
	mlx_image_t		*img;
	double			start_x;
	double			start_y;
	double			end_x;
	double			end_y;
	uint32_t		color;
}	t_print_info;

typedef struct s_tex_var
{
	int		x;
	double	y;
	double	x_offsee;
	double	y_offset;
	double	step_x;
	double	step_y;
	t_drc	wall_side;
	double	line_h;
	double	ray;
}	t_tex_var;


typedef struct s_exe_info
{
	mlx_t		*mlx;
	mlx_image_t	*background;
	mlx_image_t	*scene;
	t_player	player;
	t_input		*map_input;
	double		pad_x;
	double		pad_y;
	double		blk_size;
}	t_exe_info;

/* draw_dda.c*/
void			draw_ray(t_exe_info *img, t_print_info *info);
void			draw_player_direction(t_exe_info *img);
/* draw_main.c*/
void			draw_background(t_exe_info *img);
int				draw_cube(t_exe_info *img);
/* draw_map.c */
void			draw_map(t_exe_info *img);
/* draw_ray_calc.c*/
void			draw_ray_scene(t_exe_info *img);
/* draw_rays_utils.c*/
void			set_print(t_exe_info *img, t_print_info *info, t_wall_pos *w_pos);
void			set_no_wall(t_player *player, t_ray *ray);
double			dist_pg_rayend(double ax, double ay, double bx, double by);
t_drc			set_direction(t_drc pos, double angle);
int				calc_max_wall_dist(t_exe_info *img);
/* draw_scene_utils.c */
uint32_t		calc_color(mlx_texture_t *texture, t_tex_var *tex);
bool			is_mini_map_space(t_exe_info *img, int y, int x);
void			set_right_ray(t_wall_pos *wall, t_tex_var *tex);
/* draw_scene.c */
void			draw_scene(t_exe_info *img,t_wall_pos *wall, int ray, double angle);
/* execution_utils.c */
bool			is_wall(char c);
/* keystroke_calc.c*/
void			hook(void *param);
/* keystroke.c*/
void			key_w(t_exe_info *img, t_wall_coll *set);
void			key_s(t_exe_info *img, t_wall_coll *set);
void			key_a(t_exe_info *img, t_wall_coll *set);
void			key_d(t_exe_info *img, t_wall_coll *set);

# endif
#endif