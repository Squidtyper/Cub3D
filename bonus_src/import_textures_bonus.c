/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   import_textures_bonus.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 17:32:02 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/20 22:07:41 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D_bonus.h"
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

mlx_texture_t	*open_texture(char *path)
{
	int				fd;
	mlx_texture_t	*tex;

	fd = open(path, O_RDONLY);
	if (fd <= 0)
	{
		printf("Error: %s: %s\n", path, strerror(errno));
		exit(1);
	}
	close(fd);
	tex = mlx_load_png(path);
	if (tex == NULL)
	{
		printf("Error: %s: file is not a png file.\n", path);
		exit(1);
	}
	return (tex);
}

void	texture_error(bool testvalue, char *what)
{
	if (testvalue == true)
	{
		printf("Error: double %s texture in input\n", what);
		exit(1);
	}
}

void	get_texture(t_input *input, char **words)
{
	if (ft_strncmp(words[0], "NO", 3) == 0)
	{
		texture_error(input->NO_found, "NO");
		input->NO_tex = open_texture(words[1]);
		input->NO_found = true;
	}
	if (ft_strncmp(words[0], "SO", 3) == 0)
	{
		texture_error(input->SO_found, "SO");
		input->SO_tex = open_texture(words[1]);
		input->SO_found = true;
	}
	if (ft_strncmp(words[0], "WE", 3) == 0)
	{
		texture_error(input->WE_found, "WE");
		input->WE_tex = open_texture(words[1]);
		input->WE_found = true;
	}
	if (ft_strncmp(words[0], "EA", 3) == 0)
	{
		texture_error(input->EA_found, "EA");
		input->EA_tex = open_texture(words[1]);
		input->EA_found = true;
	}
}

void	find_texture(t_input *input)
{
	int		i;
	char	**words;

	i = 0;
	while (input->lines[i])
	{
		words = ft_space_split(input->lines[i]);
		get_texture(input, words);
		cleardarray(words);
		i++;
	}
	input->door_tex = open_texture(DOOR);
	input->sprite_tex = open_texture(GHOSTPNG);
}
