/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:07:22 by ladloff           #+#    #+#             */
/*   Updated: 2023/05/22 01:11:18 by ladloff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_gnl
{
	size_t			buffer_index;
	char			*buffer;
	ssize_t			read_bytes;
	struct s_gnl	*next;
}	t_gnl;

/* get_next_line_bonus.c */
char	*get_next_line(int fd);

/* get_next_line_utils_bonus.c */
void	*ft_calloc(size_t count, size_t size);
t_gnl	*free_gnl_node(t_gnl *current);
t_gnl	*create_gnl_node(int fd);

#endif /* GET_NEXT_LINE_BONUS_H */
