#ifndef CUBE3D_H
# define CUBE3D_H
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# define PI 3.1415926535


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


typedef struct s_image_mlx
{
	mlx_t		*mlx;
	mlx_image_t	*map;
	t_player	player;
}	t_image_mlx;

typedef struct s_input
{
	char			*file_content;
	char			**map_points;
	int32_t			c_color;
	int32_t			f_color;
	mlx_texture_t	*NO_tex;
	mlx_texture_t	*SO_tex;
	mlx_texture_t	*WE_tex;
	mlx_texture_t	*EA_tex;
	bool			compleet;
}	t_input;

void	draw_line(t_player *player);
void	draw_lineray(t_player *player, t_rays ray);
void	draw_rays_2D (t_player *player);

void	key_w(t_image_mlx *img);
void	key_s(t_image_mlx *img);
void	key_a(t_image_mlx *img);
void	key_d(t_image_mlx *img);
void	key_left(t_image_mlx *img);
void	key_right(t_image_mlx *img);



/*-----------parsing functions-------------*/

void	ac_error(int ac);
void	mallocerr(void);
int		color_atoi(char *str);
void	cleardarray(char **array);
char	**ft_space_split(char *str);
int		open_file(char *name);
t_input *parse(int ac, char **av);
void    ac_error(int ac);
#endif