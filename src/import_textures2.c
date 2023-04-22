/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   import_textures2.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/22 18:16:46 by lizhang       #+#    #+#                 */
/*   Updated: 2023/04/22 18:26:50 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
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
	free(path);
	return (tex);
}

void	texture_error(bool testvalue, char *what)
{
	if (testvalue == true)
	{
		printf("Error: multiple %s texture in input\n", what);
		exit(1);
	}
}

void	get_texture(t_tex_all *col, char *ind, char *line)
{
	if (ft_strncmp(ind, "NO", 3) == 0)
	{
		texture_error(col->no_found, "NO");
		col->no_tex = open_texture(get_tex_path(line));
		col->no_found = true;
	}
	if (ft_strncmp(ind, "SO", 3) == 0)
	{
		texture_error(col->so_found, "SO");
		col->so_tex = open_texture(get_tex_path(line));
		col->so_found = true;
	}
	if (ft_strncmp(ind, "WE", 3) == 0)
	{
		texture_error(col->we_found, "WE");
		col->we_tex = open_texture(get_tex_path(line));
		col->we_found = true;
	}
	if (ft_strncmp(ind, "EA", 3) == 0)
	{
		texture_error(col->ea_found, "EA");
		col->ea_tex = open_texture(get_tex_path(line));
		col->ea_found = true;
	}
}
