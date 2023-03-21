/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/18 20:56:46 by lizhang       #+#    #+#                 */
/*   Updated: 2021/10/16 16:30:19 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*p;
	size_t	count;
	size_t	size;

	count = 0;
	size = ft_strlen (s1);
	p = ft_calloc (size + 1, sizeof(char));
	if (p == NULL)
		return (NULL);
	while (count < size)
	{
		p[count] = s1[count];
		count++;
	}
	return (p);
}
