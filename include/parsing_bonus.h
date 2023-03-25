/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_bonus.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 14:52:22 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/25 19:21:22 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_BONUS_H
#define PARSING_BONUS_H
# include <readline/readline.h>
# include <fcntl.h>

# include "../MLX42/include/MLX42/MLX42.h"
#include "../libft/libft.h"

typedef struct s_f_con
{
	char			*file_content;
	char			**lines;
}	t_f_con;

typedef struct s_input
{
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
	mlx_texture_t	*door_tex;
	bool			door_found;//2 for doors
	mlx_texture_t	*sprite_tex;	
	bool			sprite_found;//G for sprite
	float			a_player;
	int				player_x;
	int				player_y;
	bool			p_found;
}	t_input;

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
void			find_color(t_input *input, t_f_con *f_con);
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