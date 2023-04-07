/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_bonus.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/07 19:51:05 by lizhang       #+#    #+#                 */
/*   Updated: 2023/04/07 19:51:05 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

int	main(int ac, char **av)
{
	t_input	*input;

	input = parse_bonus(ac, av);
	execution(input);
	clean_input(input);
	return (EXIT_SUCCESS);
}
