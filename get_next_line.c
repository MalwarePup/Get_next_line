/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 09:55:21 by ladloff           #+#    #+#             */
/*   Updated: 2024/03/16 01:42:57 by ladloff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/select.h>
#include "get_next_line.h"

static char	*extract_line(t_gnl **list, size_t line_size)
{
	size_t	i;
	char	*line;
	char	*p_line;

	if (!list || !(*list))
		return (NULL);
	line = ft_calloc((line_size + 1), sizeof(char));
	if (!line)
		return (NULL);
	p_line = line;
	i = (*list)->buffer_index;
	while (line_size--)
	{
		*line++ = (*list)->buffer[i++];
		if ((size_t)(*list)->read_bytes == i)
		{
			*list = free_gnl_node(*list);
			i = 0;
		}
	}
	*line = '\0';
	if (*list)
		(*list)->buffer_index = i;
	return (p_line);
}

static size_t	get_line_size(t_gnl *list, int fd)
{
	size_t	i;
	size_t	line_size;
	t_gnl	*new_node;

	if (!list || !list->buffer)
		return (0);
	line_size = 1;
	i = list->buffer_index;
	while (list->buffer[i] && list->buffer[i++] != '\n')
	{
		if ((size_t)list->read_bytes == i)
		{
			new_node = create_gnl_node(fd);
			if (!new_node)
				return (0);
			new_node->next = list->next;
			list->next = new_node;
			list = new_node;
			i = 0;
		}
		line_size++;
	}
	return (line_size);
}

char	*get_next_line(int fd)
{
	static t_gnl	*list;
	char			*line;
	size_t			line_size;

	line = NULL;
	if (fd >= 0 && fd < FD_SETSIZE)
	{
		if (!list)
			list = create_gnl_node(fd);
		if (list && list->read_bytes)
		{
			line_size = get_line_size(list, fd);
			if (line_size)
				line = extract_line(&list, line_size);
		}
		else
			list = free_gnl_node(list);
	}
	return (line);
}
