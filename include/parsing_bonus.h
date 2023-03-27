/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_bonus.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 14:52:22 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/27 18:08:45 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_BONUS_H
#define PARSING_BONUS_H
# include <readline/readline.h>
# include <fcntl.h>
# include <stdio.h>
# include "cube3D.h"
# include "parsing.h" 
# include "../MLX42/include/MLX42/MLX42.h"
# define GHOSTPNG "../textures/king_boo.png"
# define DOORPNG "../textures/whirlpool.png"

typedef struct s_tex_bonus
{
	mlx_texture_t	*door_tex;
	bool			door_found;
	mlx_texture_t	*sprite_tex;
	bool			sprite_found;
}	t_tex_bonus;

typedef struct s_check_bonus
{
	t_check			*check;
	t_tex_bonus		*tex_bonus;
}	t_check_bonus;

//read_input_bonus:
void			pre_fill_bonus(t_check_bonus *check);
t_input			*parse_bonus(int ac, char **av);

//get_map_bonus:
int				valid_map_line_bonus(char *str);
void			find_map_bonus(t_check_bonus *check, char **lines);

//get_player_bonus:
void			fill_input_bonus(int x, int y, t_check_bonus *check, char c);
void			get_player_bonus(t_check_bonus *check);

//import_texture_bonus:
void			get_texture_bonus(t_tex_bonus *tex_bonus);
void			find_texture_bonus(t_check_bonus *check, char **lines);

//test_inputs_bonus:
void			test_var_bonus(t_check_bonus *check);
void			test_inputs_bonus(t_check_bonus *check);

//boundary_test:
void			boundary_test_bonus(char **m_p, unsigned int height, unsigned int width);
#endif