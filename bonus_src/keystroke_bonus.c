/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keystroke_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmonfrin <dmonfrin@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/04 11:46:57 by dmonfrin      #+#    #+#                 */
/*   Updated: 2023/04/04 11:46:58 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution_bonus.h"
#include <math.h>

void	key_w(t_exe_info *img, t_obj_seen *wall, t_obj_seen *door)
{
	if (!is_wall(img->map_input->map_points[wall->ipy][wall->ipx_add_xo]))
		img->player.pos.x += img->player.delta.x;
	if (!is_wall(img->map_input->map_points[wall->ipy_add_yo][wall->ipx]))
		img->player.pos.y += img->player.delta.y;
	if (img->map_input->map_points[door->ipy][door->ipx_sub_xo] == 'O')
		img->map_input->map_points[door->ipy][door->ipx_sub_xo] = '2';
	if (img->map_input->map_points[door->ipy_sub_yo][door->ipx] == 'O')
		img->map_input->map_points[door->ipy_sub_yo][door->ipx] = '2';
}

void	key_s(t_exe_info *img, t_obj_seen *wall, t_obj_seen *door)
{
	if (!is_wall(img->map_input->map_points[wall->ipy][wall->ipx_sub_xo]))
		img->player.pos.x -= img->player.delta.x;
	if (!is_wall(img->map_input->map_points[wall->ipy_sub_yo][wall->ipx]))
		img->player.pos.y -= img->player.delta.y;
	if (img->map_input->map_points[door->ipy][door->ipx_add_xo] == 'O')
		img->map_input->map_points[door->ipy][door->ipx_add_xo] = '2';
	if (img->map_input->map_points[door->ipy_add_yo][door->ipx] == 'O')
		img->map_input->map_points[door->ipy_add_yo][door->ipx] = '2';
}

void	key_a(t_exe_info *img, t_obj_seen *wall, t_obj_seen *door)
{
	if (!is_wall(img->map_input->map_points[wall->ipy][wall->ipx_add_yo]))
		img->player.pos.x += img->player.delta.y;
	if (!is_wall(img->map_input->map_points[wall->ipy_sub_xo][wall->ipx]))
		img->player.pos.y -= img->player.delta.x;
	if (img->map_input->map_points[door->ipy][door->ipx_sub_yo] == 'O')
		img->map_input->map_points[door->ipy][door->ipx_sub_yo] = '2';
	if (img->map_input->map_points[door->ipy_add_xo][door->ipx] == 'O')
		img->map_input->map_points[door->ipy_add_xo][door->ipx] = '2';
}

void	key_d(t_exe_info *img, t_obj_seen *wall, t_obj_seen *door)
{
	if (!is_wall(img->map_input->map_points[wall->ipy][wall->ipx_sub_yo]))
		img->player.pos.x -= img->player.delta.y;
	if (!is_wall(img->map_input->map_points[wall->ipy_add_xo][wall->ipx]))
		img->player.pos.y += img->player.delta.x;
	if (img->map_input->map_points[door->ipy][door->ipx_add_yo] == 'O')
		img->map_input->map_points[door->ipy][door->ipx_add_yo] = '2';
	if (img->map_input->map_points[door->ipy_sub_xo][door->ipx] == 'O')
		img->map_input->map_points[door->ipy_sub_xo][door->ipx] = '2';
}

void	key_space(t_exe_info *info, t_obj_seen *door)
{
	if (info->map_input->map_points[door->ipy][door->ipx_add_xo] == '2')
		info->map_input->map_points[door->ipy][door->ipx_add_xo] = 'O';
	if (info->map_input->map_points[door->ipy_add_yo][door->ipx] == '2')
		info->map_input->map_points[door->ipy_add_yo][door->ipx] = 'O';
}
