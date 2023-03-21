#ifndef CUBE3D_H
# define CUBE3D_H
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# define HEIGHT_WIDTH 512


typedef struct s_input
{
	char			*file_content;	
	char			**lines;
	char			**map_points;
	unsigned int	map_width;
	unsigned int	map_height;
	long long		c_color;
	bool			c_found;
	long long		f_color;		
	bool			f_found;
	mlx_texture_t	*NO_tex;
	bool			NO_found;
	mlx_texture_t	*SO_tex;
	bool			SO_found;
	mlx_texture_t	*WE_tex;
	bool			WE_found;
	mlx_texture_t	*EA_tex;
	bool			EA_found;
	double			a_player;
	int				player_x;
	int				player_y;
	bool			p_found;
}	t_input;

void		execution(t_input *input);
t_input 	*parse(int ac, char **av);

/*-----------parsing functions-------------*/

void			ac_error(int ac);
void			mallocerr(void);
int				color_atoi(char *str);
void			cleardarray(char **array);
char			*join_free(char *str1, char *str2);
char			**ft_space_split(char *str);
int				open_file(char *name);
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