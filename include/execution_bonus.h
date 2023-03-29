#ifndef EXECUTION_BONUS_H
# define EXECUTION_BONUS_H
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
	FRONT_DOOR,
	OPPOSITE_DOOR,
}	t_drc;

typedef enum e_num
{
	FOV = 60,
}t_num;

typedef struct s_axis
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

typedef struct s_tex_var
{
	t_axis	base;
	t_axis	offset;
	t_axis	step;
	t_drc	wall_side;
	double	line_h;
	double	ray;
}t_tex_var;

typedef struct s_print_info
{
	mlx_image_t	*img;
	uint32_t	color;
	t_axis		start_point;
	t_axis		end_point;
}t_print_info;

typedef struct s_exe_info
{
	mlx_t		*mlx;
	mlx_image_t	*background;
	mlx_image_t	*scene;
	t_player	player;
	t_input		*map_input;
	t_axis		pad;
	double		size;
	t_axis	sprite;
}t_exe_info;


/* draw_dda.c*/
void			draw_ray(t_exe_info *img, t_print_info *info);
void			draw_player_direction(t_exe_info *img);

/* draw_main.c */
int				draw_cube(t_exe_info *img);
void			draw_background(t_exe_info *img);
/* draw_map_bonus.c */
void			draw_map(t_exe_info *img);
/* rays_calc.c*/
void			find_vert_wall(t_exe_info *img, t_wall_pos *w_pos, double angle);
void			find_horiz_wall(t_exe_info *img, t_wall_pos *w_pos, double angle);
/* draw_scene_utils_bonus.c */
uint32_t		calc_color(mlx_texture_t *texture, t_tex_var *tex);
bool			is_mini_map_space(t_exe_info *img, int y, int x);
void			set_right_ray(t_wall_pos *wall, t_tex_var *tex);
/* execution_init.c */
int				init_info(t_exe_info *info);
/* execution_utils_bonus.c */
bool			is_wall(char c);
t_drc			set_wall_side(t_exe_info *info, t_wall_pos *wall);
/* hook_loop_bonus.c*/
void			hook(void *param);
/* keystroke_calc_bonus.c*/
void			keystroke(t_exe_info *info, t_object_seen *wall, t_object_seen *door);
void			wall_collision(t_exe_info *info, t_object_seen *wall);
void			door_closing(t_exe_info *info, t_object_seen *door);
/* keystroke_bonus.c*/
void			key_w(t_exe_info *img, t_object_seen *waal, t_object_seen *door);
void			key_s(t_exe_info *img, t_object_seen *wall, t_object_seen *door);
void			key_a(t_exe_info *img, t_object_seen *wall,  t_object_seen *door);
void			key_d(t_exe_info *img, t_object_seen *wall,  t_object_seen *door);
void			key_space(t_exe_info *img);
/* rays_utils.c*/
void			set_print(t_exe_info *img, t_print_info *info,
					t_wall_pos *w_pos);
void			angle_normalizer(double *angle);					
/* sprite_bonus.c*/
void			draw_sprite(t_exe_info *info, double *is_visible_sprite);
void			look_for_sprite(t_exe_info *info);

#endif
