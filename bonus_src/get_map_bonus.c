/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_map_bonus.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/10 18:13:19 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/20 21:36:48 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

int	valid_map_line_bonus(char *str)
{
	int	i;
	int	n_digit;

	i = 0;
	n_digit = 0;
	while (str[i])
	{
		if (str[i] != 13 && str[i] != '	' && str[i] != 'N' && str[i] != 'S' \
		&& str[i] != 'W' && str[i] != 'E' && ft_isdigit(str[i]) == 0)
			return (0);
		if (ft_isdigit(str[i]) == 1)
			n_digit++;
		i++;
	}
	if (n_digit == 0)
		return (0);
	return (1);
}

void	find_map_bonus(t_check_bonus *checkb, char **lines)
{
	int		i;
	t_list	*map;
	t_list	*item;

	i = 0;
	map = NULL;
	while (lines[i])
	{
		if (ft_strlen(lines[i]) > 3 && only_digits(lines[i]) == 1)
			break ;
		i++;
	}
	while (lines[i] && ft_strlen(lines[i]) > 3 && \
	valid_map_line_bonus(lines[i]) == 1)
	{
		item = ft_lstnew(ft_strdup(lines[i]));
		ft_lstadd_back(&map, item);
		i++;
	}
	if (ft_lstsize(map) < 3)
	{
		printf("Error: map does not suffice\n");
		exit(1);
	}
	checkb->check->input->map_points = convert_map(map, checkb->check->input);
}
