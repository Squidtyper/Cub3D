/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/03 17:20:51 by lizhang       #+#    #+#                 */
/*   Updated: 2023/04/03 17:20:51 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

int	main(int ac, char **av)
{
	t_input	*input;

	input = parse(ac, av);
	execution(input);
	clean_input(input);
	return (EXIT_SUCCESS);
}
