/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_bonus.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 14:52:22 by lizhang       #+#    #+#                 */
/*   Updated: 2023/04/22 18:47:55 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_BONUS_H
# define PARSING_BONUS_H
# include <readline/readline.h>
# include <fcntl.h>
# include <stdio.h>
# include "cube3D.h"
# include "parsing.h" 
# include "../MLX42/include/MLX42/MLX42.h"
# define DOORPNG "textures/door.png"

typedef struct s_tex_bonus
{
	mlx_texture_t	*door_tex;
	bool			door_found;
}	t_tex_bonus;

typedef struct s_check_bonus
{
	t_check			*check;
	t_tex_bonus		*tex_bonus;
}	t_check_bonus;

//parsing_clean_bonus:
void			parsing_clean_bonus(t_check_bonus *checkb);

//read_input_bonus:
t_check			*man_parse(char **lines);
t_check_bonus	*checkb_init(void);
t_input			*parse_bonus(int ac, char **av);

//get_map_bonus:
int				valid_map_line_bonus(char *str);
void			map_basic_check_bonus(t_list *map, char **lines, int i, \
				t_check_bonus *checkb);
void			find_map_bonus(t_check_bonus *check, char **lines);

//import_texture_bonus:
void			get_texture_bonus(t_tex_bonus *tex_bonus);
void			find_texture_bonus(t_check_bonus *check, char **lines);

//boundary_test:
void			boundary_test_bonus(char **m_p, unsigned int height, \
unsigned int width);
#endif