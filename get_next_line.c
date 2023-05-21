/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 09:55:21 by ladloff           #+#    #+#             */
/*   Updated: 2023/05/22 00:27:37 by ladloff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/select.h>
#include "get_next_line.h"

static char	*extract_line(t_list **lst, size_t line_size)
{
	ssize_t	i;
	char	*line;
	char	*p_line;

	if (!lst || !(*lst))
		return (NULL);
	line = malloc((line_size + 1) * sizeof(char));
	if (!line)
		return (NULL);
	p_line = line;
	i = (*lst)->i;
	while (line_size--)
	{
		*line++ = (*lst)->buffer[i++];
		if ((*lst)->read_bytes == i)
		{
			*lst = free_t_lst(*lst);
			i = 0;
		}
	}
	*line = '\0';
	if (*lst)
		(*lst)->i = i;
	return (p_line);
}

static size_t	get_line_size(t_list *lst, int fd)
{
	ssize_t	i;
	size_t	line_size;
	t_list	*new_node;

	if (!lst || !lst->buffer)
		return (0);
	line_size = 1;
	i = lst->i;
	while (lst->buffer[i] && lst->buffer[i++] != '\n')
	{
		if (lst->read_bytes == i)
		{
			new_node = create_t_list_node(fd);
			if (!new_node)
				return (0);
			new_node->next = lst->next;
			lst->next = new_node;
			lst = new_node;
			i = 0;
		}
		line_size++;
	}
	return (line_size);
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	char			*line;
	size_t			line_size;

	if (fd < 0 || fd >= FD_SETSIZE)
		return (NULL);
	if (!lst)
		lst = create_t_list_node(fd);
	if (!lst)
		return (NULL);
	if (!lst->read_bytes)
	{
		lst = free_t_lst(lst);
		return (NULL);
	}
	line_size = get_line_size(lst, fd);
	if (!line_size)
		return (NULL);
	line = extract_line(&lst, line_size);
	return (line);
}
