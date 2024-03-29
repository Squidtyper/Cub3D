/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cube3D.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/07 20:16:15 by lizhang       #+#    #+#                 */
/*   Updated: 2023/04/07 20:16:17 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# include "../libft/libft.h"

typedef struct s_input
{
	char			**map_points;
	unsigned int	map_width;
	unsigned int	map_height;
	long long		c_color;
	long long		f_color;
	t_list			*textures;
	float			a_player;
	int				player_x;
	int				player_y;
}	t_input;

void		execution(t_input *input);
t_input		*parse(int ac, char **av);
void		clean_input(t_input *input);

#endif
