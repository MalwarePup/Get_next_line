/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:10:10 by ladloff           #+#    #+#             */
/*   Updated: 2023/05/22 01:32:10 by ladloff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "get_next_line_bonus.h"

static void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p_s;

	p_s = s;
	while (n-- > 0)
		*p_s++ = 0;
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	void	*p;

	if (!count || !size)
		return (NULL);
	if (count > ULONG_MAX / 2 || size > ULONG_MAX / 2)
		return (NULL);
	total_size = count * size;
	p = malloc(total_size);
	if (!p)
		return (NULL);
	ft_bzero(p, total_size);
	return (p);
}

t_gnl	*free_gnl_node(t_gnl *current)
{
	t_gnl	*next;

	if (!current)
		return (NULL);
	next = current->next;
	free(current->buffer);
	free(current);
	return (next);
}

t_gnl	*create_gnl_node(int fd)
{
	t_gnl	*new_node;

	new_node = ft_calloc(1, sizeof(t_gnl));
	if (!new_node)
		return (NULL);
	new_node->buffer = ft_calloc(BUFFER_SIZE, sizeof(char));
	if (!new_node->buffer)
	{
		free(new_node);
		return (NULL);
	}
	new_node->read_bytes = read(fd, new_node->buffer, BUFFER_SIZE);
	if (new_node->read_bytes < 0)
	{
		free(new_node->buffer);
		free(new_node);
		return (NULL);
	}
	return (new_node);
}
