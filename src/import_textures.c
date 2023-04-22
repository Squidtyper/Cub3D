/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   import_textures.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 17:32:02 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/20 16:10:05 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_tex_path(char *line)
{
	int		i;
	char	*line2;
	char	*line3;
	char	*line4;

	i = 0;
	line2 = clear_str_space(line);
	while (line2[i] && ft_isalpha(line2[i]) == 1)
		i++;
	while (line2[i] && (line2[i] == 32 || line2[i] == 9 \
	|| line2[i] == 13))
		i++;
	line3 = ft_substr(line2, i, ft_strlen(line2) - i);
	line4 = rm_nl(line3);
	free(line2);
	free(line3);
	return (line4);
}

t_list	*texture_to_list(t_tex_all *col)
{
	t_list	*textures;

	textures = ft_lstnew(col->no_tex);
	ft_lstadd_back(&textures, ft_lstnew(col->so_tex));
	ft_lstadd_back(&textures, ft_lstnew(col->we_tex));
	ft_lstadd_back(&textures, ft_lstnew(col->ea_tex));
	return (textures);
}

void	tex_init(t_check *check)
{
	check->tex = (t_tex_all *)malloc(sizeof(t_tex_all));
	if (!check->tex)
	{
		mallocerr();
		parsing_clean(check);
	}
	check->tex->no_found = false;
	check->tex->ea_found = false;
	check->tex->so_found = false;
	check->tex->we_found = false;
}

void	find_texture(t_check *check, char **lines)
{
	int			i;
	char		**words;

	i = 0;
	tex_init(check);
	while (lines[i])
	{
		words = ft_space_split(lines[i]);
		if (!words)
		{
			mallocerr();
			cleardarray(lines);
			parsing_clean(check);
		}
		if (words[0])
			get_texture(check->tex, words[0], lines[i]);
		cleardarray(words);
		i++;
	}
	check_textures(check);
	check->input->textures = texture_to_list(check->tex);
	free(check->tex);
	check->tex = NULL;
}
