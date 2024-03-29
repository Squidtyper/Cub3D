/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 14:52:22 by lizhang       #+#    #+#                 */
/*   Updated: 2023/04/24 16:55:57 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include <readline/readline.h>
# include <fcntl.h>
# include <stdio.h>
# include "cube3D.h"
# include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_tex_all
{
	mlx_texture_t	*no_tex;
	bool			no_found;
	mlx_texture_t	*so_tex;
	bool			so_found;
	mlx_texture_t	*we_tex;
	bool			we_found;
	mlx_texture_t	*ea_tex;
	bool			ea_found;
}	t_tex_all;

typedef struct s_check
{
	t_input			*input;
	bool			c_found;
	bool			f_found;
	bool			p_found;
	t_tex_all		*tex;
}	t_check;

//parse_utils:
char			*join_free(char *str1, char *str2);
bool			only_digits(char *str);
char			*clear_str_space(char *str);
char			*rm_vertical_tab(char *str);
char			*rm_nl(char *str);

//error_messages:
void			ac_error(int ac);
void			mallocerr(void);
void			color_incorrect(t_check *check);
void			color_double(bool testvalue, t_check *check);
int				color_atoi(char *str, t_check *check);

//ft_space_split:
char			**ft_space_split(char *str);

//read_input:
int				open_file(char *name);
t_list			*read_file(char *name);
void			pre_fill(t_check *check);
char			**file_lines(char *path);
t_input			*parse(int ac, char **av);

//parse_color2:
long long		color_comb(char *r, char *g, char *b, t_check *check);
void			parse_color(char *ind, char **colors, t_check *check);

//parse_color:
char			*combine_lines(char **words);
void			too_many_color(char *colorline, char **lines, t_check *check);
void			color_fill(char **colors, char *colorline, char **lines, \
				t_check *check);
char			**color_check(char **words, char **lines, t_check *check);
void			find_color(t_check *check, char **lines);

//get_map2:
char			*fill_map_line(char *content, unsigned int len);
unsigned int	get_map_width(t_list *map);
char			**convert_map(t_list *map, t_input *input);

//get_map:
int				valid_map_line(char *str);
void			map_basic_check(t_list *map, char **lines, int i, \
				t_check *check);
void			find_map(t_check *check, char **lines);

//get_player:
void			player_error(char c);
double			get_angle(char c);
void			fill_input(int x, int y, t_check *check, char c);
void			get_player(t_check *check);

//import texture 2:
mlx_texture_t	*open_texture(char *path);
void			texture_error(bool testvalue, char *what);
void			get_texture(t_tex_all *col, char *ind, char *path);

//import texture:
char			*get_tex_path(char *line);
t_list			*texture_to_list(t_tex_all *col);
void			tex_init(t_check *check);
void			find_texture(t_check *check, char **lines);
char			*get_tex_path(char *line);

//test_inputs:
void			test_var(t_check *check);
void			test_inputs(t_check *check);
void			check_textures(t_check *check);

//boundary_test:
bool			boundary_test(char **m_p, unsigned int height, \
unsigned int width);

//clean_parsing:
void			cleardarray(char **array);
void			clean_input(t_input *input);
void			tex_clean(t_tex_all *tex);
void			parsing_clean(t_check *check);

#endif