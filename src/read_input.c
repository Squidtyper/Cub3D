/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/05 15:40:57 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/17 16:00:05 by dmonfrin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <math.h>
#include <errno.h>

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
	input->map_points = NULL;
	input->c_color = 0;
	input->f_color = 0;
	input->c_found = false;
	input->f_found = false;
	input->textures = NULL;
	input->a_player = 0;
	input->player_x = 0;
	input->player_y = 0;
	input->p_found = false;
}

void	find_map(t_input *input, t_f_con *f_con)
{
	int		i;
	t_list	*map;
	t_list	*item;

	i = 0;
	map = NULL;
	while (f_con->lines[i])
	{
		if (ft_strlen(f_con->lines[i]) > 3 && only_digits(f_con->lines[i]) == 1)
			break ;
		i++;
	}
	while (f_con->lines[i] && ft_strlen(f_con->lines[i]) > 3 && \
	valid_map_line(f_con->lines[i]) == 1)
	{
		item = ft_lstnew(ft_strdup(f_con->lines[i]));
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
	t_f_con *f_con;

	ac_error(ac);
	input = (t_input *)malloc(sizeof(t_input));
	if (!input)
		mallocerr();
	pre_fill(input);
	f_con = (t_f_con *)malloc(sizeof(t_f_con));
	f_con->file_content = read_file(av[1]);
	find_color(input, f_con);
	find_texture(input, f_con);
	find_map(input, f_con);
	get_player(input);
	test_inputs(input);
	boundary_test(input->map_points, input->map_height, input->map_width);
	return (input);
}
