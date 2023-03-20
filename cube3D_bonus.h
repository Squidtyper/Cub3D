#ifndef CUBE3D_BONUS_H
# define CUBE3D_BONUS_H
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# define PI 3.1415926535
# define P2 PI/2
# define P3 3*PI/2
# define DR 0.0174533 //one degree in radians
# define DOOR "./whirlpool.png"
# define GHOSTPNG "./king_boo.png"

extern uint32_t	mappa [];

extern size_t map_x;
extern size_t map_y;

typedef struct s_rays
{
	int map_x;
	int map_y;
	int map_pos;
	int dof;
	int i_ray;
	double x;
	double y;
	double angle;
	double x_offset;
	double y_offset;
} t_rays;

typedef struct s_player
{
	mlx_image_t	*img;
	double x;
	double y;
	double delta_x;
	double delta_y;
	double angle;
}	t_player;

typedef struct s_wall_coll
{
	int	x_offset;
	int y_offset;
	int ipx;
	int ipx_add_xo;
	int ipx_sub_xo;
	int ipy;
	int ipy_add_yo;
	int ipy_sub_yo;
}	t_wall_coll;

typedef struct s_ray_end
{
	double	hor_x;
	double	hor_y;
	double	ver_x;
	double	ver_y;
	double	dist;
	int		pos;
} t_ray_end;

typedef struct s_print_info
{
	mlx_image_t	*img;
	double start_x;
	double start_y;
	double end_x;
	double end_y;
	uint32_t color;
}	t_print_info;

typedef struct s_input
{
	char			*file_content;	//not so important
	char			**lines;		//not so important
	char			**map_points;	//I changed the player to 0 after getting the player
	unsigned int	map_width;
	unsigned int	map_height;
	long long		c_color;		//this has changed
	bool			c_found;
	long long		f_color;		//this has changed		
	bool			f_found;
	mlx_texture_t	*NO_tex;
	bool			NO_found;
	mlx_texture_t	*SO_tex;
	bool			SO_found;
	mlx_texture_t	*WE_tex;
	bool			WE_found;
	mlx_texture_t	*EA_tex;
	bool			EA_found;
	mlx_texture_t	*door_tex;
	bool			door_found;
	mlx_texture_t	*ghost;
	bool			ghost_found;
	float			a_player;		//angle of player in radians
	int				player_x;		//location player
	int				player_y;		//location player
	bool			p_found;
}	t_input;


typedef struct s_image_mlx
{
	mlx_t		*mlx;
	mlx_image_t	*map;
	t_player	player;
	t_input		*map_input;
}	t_image_mlx;


void	draw_player(t_image_mlx *img);
void	draw_line(t_player *player);
void	draw_lineray(t_print_info *info);
void	draw_rays_2D (t_player *player);
void	draw3d(t_print_info *info);
void	scene3d(t_ray_end *rays, int ray, double angle, t_player *player);

void	hook(void* param);
void	key_w(t_image_mlx *img, t_wall_coll *set);
void	key_s(t_image_mlx *img, t_wall_coll *set);
void	key_a(t_image_mlx *img, t_wall_coll *set);
void	key_d(t_image_mlx *img, t_wall_coll *set);
void	key_left(t_image_mlx *img);
void	key_right(t_image_mlx *img);

/*-----------parsing functions-------------*/

void			ac_error(int ac);
void			mallocerr(void);
int				color_atoi(char *str);
void			cleardarray(char **array);
char			*join_free(char *str1, char *str2);
char			**ft_space_split(char *str);
int				open_file(char *name);
t_input 		*parse(int ac, char **av);
void    		ac_error(int ac);
void			parse_color(char **words, t_input *input);
void			color_double(bool testvalue);
void			find_color(t_input *input);
int				only_digits(char *str);
void			find_texture(t_input *input);
void			get_player(t_input *input);
int				valid_map_line(char *str);
char			**convert_map(t_list *map, t_input *input);
char			*fill_map_line(char *content, unsigned int len);
void			find_texture(t_input *input);
mlx_texture_t	*open_texture(char *path);
void			boundary_test(char **m_p, unsigned int height, unsigned int width);
void			test_inputs(t_input *input);
void			clean_input(t_input *input);
#endif