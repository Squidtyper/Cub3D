/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/25 22:09:04 by lizhang       #+#    #+#                 */
/*   Updated: 2023/03/14 19:06:27 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*buf;

	size = 0;
	buf = lst;
	while (buf)
	{
		size++;
		buf = buf->next;
	}
	return (size);
}
