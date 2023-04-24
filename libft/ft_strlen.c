/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/27 19:16:13 by lizhang       #+#    #+#                 */
/*   Updated: 2021/10/03 14:34:35 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	n;
	char	*c;

	n = 0;
	c = (char *) s;
	if (c[0] == 0)
	{
		return (0);
	}
	else
	{
		while (c[n] != 0)
			n++;
		return (n);
	}
}
