/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:10:10 by ladloff           #+#    #+#             */
/*   Updated: 2023/03/04 17:13:41 by ladloff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <limits.h>

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

t_list	*free_t_lst(t_list *lst)
{
	t_list	*next_node;

	if (!lst)
		return (NULL);
	next_node = lst->next;
	free(lst->buffer);
	free(lst);
	lst = NULL;
	return (next_node);
}

t_list	*create_t_list_node(int fd)
{
	t_list	*new_node;

	new_node = ft_calloc(1, sizeof(t_list));
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
		free_t_lst(new_node);
		return (NULL);
	}
	new_node->i = 0;
	new_node->next = NULL;
	return (new_node);
}
