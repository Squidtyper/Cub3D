/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/05 15:40:57 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/14 19:43:10 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"
#include <readline/readline.h>
#include <math.h>

int	open_file(char *name)
{
	int		fd_file;

	fd_file = open(name, O_RDONLY);
	if (fd_file <= 0)
	{
		printf("Error: %s: %s\n", name, strerror(errno));
		exit(1);
	}
	return (fd_file);
}

char	*read_file(char *name)
{
	int		file_fd;
	char	*content;
	char	*buf;

	content = NULL;
	if (ft_strncmp(name + ((ft_strlen(name) - 4)), ".cub", 4) != 0)
	{
		printf("Error: %s: file is not .cub format", name);
		exit(1);
	}
	file_fd = open_file(name);
	buf = get_next_line(file_fd);
	while (buf)
	{
		content = join_free(content, buf);
		buf = get_next_line(file_fd);
	}
	return (content);
}

void	pre_fill(t_input *input)
{
	input->file_content = NULL;
	input->lines = NULL;
	input->map_points = NULL;
	input->c_color = 0;
	input->f_color = 0;
	input->c_found = false;
	input->f_found = false;
	input->NO_tex = NULL;
	input->SO_tex = NULL;
	input->WE_tex = NULL;
	input->EA_tex = NULL;
	input->a_player = 0;
	input->player_x = 0;
	input->player_y = 0;
	input->p_found = false;
}

void	find_map(t_input *input)
{
	int		i;
	t_list	*map;
	t_list	*item;

	i = 0;
	map = NULL;
	while (input->lines[i])
	{
		if (ft_strlen(input->lines[i]) > 3 && only_digits(input->lines[i]) == 1)
			break ;
		i++;
	}
	while (input->lines[i] && ft_strlen(input->lines[i]) > 3 && \
	valid_map_line(input->lines[i]) == 1)
	{
		item = ft_lstnew(ft_strdup(input->lines[i]));
		ft_lstadd_back(&map, item);
		i++;
	}
	if (ft_lstsize(map) < 3)
	{
		printf("Error: map does not suffice\n");
		exit(1);
	}
	input->map_points = convert_map(map, input);
}

t_input	*parse(int ac, char **av)
{
	t_input	*input;

	ac_error(ac);
	input = (t_input *)malloc(sizeof(t_input));
	pre_fill(input);
	if (!input)
		mallocerr();
	input->file_content = read_file(av[1]);
	find_color(input);
	find_texture(input);
	find_map(input);
	get_player(input);
	test_inputs(input);
	boundary_test(input->map_points, input->map_height, input->map_width);
	return (input);
}
