/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 14:52:22 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/26 19:12:42 by lizhang       ########   odam.nl         */
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

char			*clear_str_space(char *str);
void			ac_error(int ac);
void			mallocerr(void);
int				color_atoi(char *str);
void			cleardarray(char **array);
char			*join_free(char *str1, char *str2);
char			**ft_space_split(char *str);
char			*rm_vertical_tab(char *str);
int				open_file(char *name);
void    		ac_error(int ac);
void			parse_color(char **words, t_check *check);
void			color_double(bool testvalue);
void			find_color(t_check *check, char **lines);
void			find_map(t_check *check, char **lines);
bool			only_digits(char *str);
void			find_texture(t_check *check, char **lines);
void			get_player(t_check *check);
int				valid_map_line(char *str);
char			**convert_map(t_list *map, t_input *input);
char			*fill_map_line(char *content, unsigned int len);
mlx_texture_t	*open_texture(char *path);
void			boundary_test(char **m_p, unsigned int height, unsigned int width);
void			test_inputs(t_check *check);


#endif