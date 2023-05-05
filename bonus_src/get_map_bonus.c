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
		if (str[i] != 'G' && str[i] != 45 && str[i] != '\n' && str[i] != 'N' && \
		str[i] != 'S' && str[i] != 'W' && str[i] != 'E' && str[i] != ' ' && \
		ft_isdigit(str[i]) == 0)
			return (0);
		if (ft_isdigit(str[i]) == 1)
			n_digit++;
		i++;
	}
	if (n_digit == 0)
		return (0);
	return (1);
}

void	map_basic_check_bonus(t_list *map, char **lines, int i, \
t_check_bonus *checkb)
{
	while (lines[i])
	{
		if ((ft_strlen(lines[i]) > 1 && !lines[i + 1]) || \
		valid_map_line(lines[i]) == 1)
		{
			if ((ft_strlen(lines[i]) && !lines[i + 1]))
				printf("Error: map is not a the end of the file.\n");
			else if (valid_map_line(lines[i]) == 1)
				printf("Error: map contains invalid line\n");
			ft_lstclear(&map, &free);
			parsing_clean_bonus(checkb);
		}
		i++;
	}
	if (ft_lstsize(map) < 3)
	{
		printf("Error: map does not suffice\n");
		ft_lstclear(&map, &free);
		parsing_clean_bonus(checkb);
	}
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
		if (ft_strlen(lines[i]) >= 3 && valid_map_line_bonus(lines[i]) == 1)
			break ;
		i++;
	}
	while (lines[i] && ft_strlen(lines[i]) >= 3 && \
	valid_map_line_bonus(lines[i]) == 1)
	{
		item = ft_lstnew(rm_nl(lines[i]));
		ft_lstadd_back(&map, item);
		i++;
	}
	map_basic_check_bonus(map, lines, i, checkb);
	checkb->check->input->map_points = convert_map(map, checkb->check->input);
}
