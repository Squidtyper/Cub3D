#ifndef CUBE3D_H
# define CUBE3D_H
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# define HEIGHT_WIDTH 1024

typedef struct s_input
{
	char			*file_content;
	char			**lines;
	char			**map_points;
	unsigned int	map_width;
	unsigned int	map_height;
	int32_t			c_color;
	bool			c_found;
	int32_t			f_color;
	bool			f_found;
	mlx_texture_t	*NO_tex;
	bool			NO_found;
	mlx_texture_t	*SO_tex;
	bool			SO_found;
	mlx_texture_t	*WE_tex;
	bool			WE_found;
	mlx_texture_t	*EA_tex;
	bool			EA_found;
	float			a_player;
	int				player_x;
	int				player_y;
	bool			p_found;
}	t_input;

typedef enum e_drc
{
	HORIZONTAL,
	VERTICAL,
	VERTICAL_LEFT,
	VERTICAL_RIGHT,
	HORIZONTAL_UP,
	HORIZONTAL_DOWN,
}t_drc;

typedef struct s_ray
{
	int		max_pg_view;
	double	x;
	double	y;
	double	x_offset;
	double	y_offset;
	double	tan;
}	t_ray;

typedef struct s_wall_pos
{
	double	hor_x;
	double	hor_y;
	double	ver_x;
	double	ver_y;
	double	dist;
	t_drc	side;
}	t_wall_pos;

typedef struct s_player
{
	mlx_image_t	*img;
	double		x;
	double		y;
	double		delta_x;
	double		delta_y;
	double		angle;
}	t_player;

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
	double	x;
	double	y;
	double	x_offsee;
	double	y_offset;
	double	step_x;
	double	step_y;
	t_drc	wall_side;
	double	line_h;
	double	ray;
}	t_tex_var;


typedef struct s_image_mlx
{
	mlx_t		*mlx;
	mlx_image_t	*map;
	t_player	player;
	t_input		*map_input;
	double		pad_x;
	double		pad_y;
	double		blk_size;
}	t_image_mlx;

void			hook(void *param);
void			draw_fixed_element(t_image_mlx *img);
void			draw_cube(t_image_mlx *img);
void			draw_ray(t_image_mlx *img, t_print_info *info);
void			draw_rays_view(t_image_mlx *img);
void			draw_map(t_image_mlx *img);
void			draw_player_direction(t_image_mlx *img);
void			draw_scene(t_image_mlx *img,t_wall_pos *wall, int ray, double angle);
void			set_print(t_image_mlx *img, t_print_info *info, t_wall_pos *w_pos);
void			set_no_wall(t_player *player, t_ray *ray);
double			dist_pg_rayend(double ax, double ay, double bx, double by);
t_drc			set_direction(t_drc pos, double angle);
void			key_w(t_image_mlx *img, t_wall_coll *set);
void			key_s(t_image_mlx *img, t_wall_coll *set);
void			key_a(t_image_mlx *img, t_wall_coll *set);
void			key_d(t_image_mlx *img, t_wall_coll *set);
mlx_texture_t	*calculate_texture(t_image_mlx *img, t_tex_var *tex);
double			calculate_x(t_image_mlx *img, mlx_texture_t *text, t_tex_var *tex);
void			set_right_ray(t_wall_pos *wall, t_tex_var *tex);
uint32_t		calc_color(mlx_texture_t *texture, int position);

/*-----------parsing functions-------------*/

mlx_texture_t*	open_texture(char *path);
void			ac_error(int ac);
void	mallocerr(void);
int		color_atoi(char *str);
void	cleardarray(char **array);
char	*join_free(char *str1, char *str2);
char	**ft_space_split(char *str);
int		open_file(char *name);
t_input	*parse(int ac, char **av);
void	ac_error(int ac);
void	find_color(t_input *input);
void	find_texture(t_input *input);
void	get_player(t_input *input);
int		valid_map_line(char *str);
char	**convert_map(t_list *map, t_input *input);
void	fill_map_line(char *to_fill, char *content, unsigned int len);
void	find_texture(t_input *input);
void	test_inputs(t_input *input);
#endif