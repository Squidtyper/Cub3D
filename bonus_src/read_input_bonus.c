/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/05 15:40:57 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/20 21:34:21 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"
#include <errno.h>

t_check	*man_parse(char **lines)
{
	t_check	*check;

	check = (t_check *)malloc(sizeof(t_check));
	if (!check)
	{
		mallocerr();
		cleardarray(lines);
		exit(EXIT_FAILURE);
	}
	pre_fill(check);
	find_color(check, lines);
	return (check);
}

t_check_bonus	*checkb_init(void)
{
	t_check_bonus	*checkb;

	checkb = (t_check_bonus *)malloc(sizeof(t_check_bonus));
	if (!checkb)
	{
		mallocerr();
		exit(EXIT_FAILURE);
	}
	checkb->tex_bonus = NULL;
	checkb->check = NULL;
	return (checkb);
}

t_input	*parse_bonus(int ac, char **av)
{
	t_check_bonus	*checkb;
	char			**lines;
	t_input			*input_r;

	ac_error(ac);
	checkb = checkb_init();
	lines = file_lines(av[1]);
	if (!lines)
		parsing_clean_bonus(checkb);
	checkb->check = man_parse(lines);
	find_texture_bonus(checkb, lines);
	input_r = checkb->check->input;
	find_map_bonus(checkb, lines);
	cleardarray(lines);
	get_player(checkb->check);
	test_inputs_bonus(checkb);
	free(checkb->check);
	free(checkb);
	return (input_r);
}
