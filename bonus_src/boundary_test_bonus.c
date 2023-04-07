/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   boundary_test_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 18:36:25 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/20 21:54:14 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

bool	test_around_bonus(char **map, unsigned int i, unsigned int j)
{
	if (ft_strchr("012GNSWE", map[i - 1][j]) == NULL || \
	ft_strchr("012GNSWE", map[i - 1][j - 1]) == NULL || \
	ft_strchr("012GNSWE", map[i - 1][j + 1]) == NULL || \
	ft_strchr("012GNSWE", map[i][j - 1]) == NULL || \
	ft_strchr("012GNSWEE", map[i][j + 1]) == NULL || \
	ft_strchr("012GNSWE", map[i + 1][j - 1]) == NULL || \
	ft_strchr("012GNSWE", map[i + 1][j]) == NULL || \
	ft_strchr("012GNSWE", map[i + 1][j + 1]) == NULL)
		return (false);
	return (true);
}

void	boundary_test_bonus(char **m_p, unsigned int height, unsigned int width)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (ft_strchr("02NSWGE", m_p[i][j]) != NULL)
			{
				if (i == 0 || i == (height - 1) || j == 0 || j == (width) || \
				test_around_bonus(m_p, i, j) == false)
				{
					printf("Error: map is not closed\n");
					exit (1);
				}
			}
			j++;
		}
		i++;
	}
}
