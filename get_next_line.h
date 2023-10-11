/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:14:04 by dklimkin          #+#    #+#             */
/*   Updated: 2023/09/26 13:14:05 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdarg.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdint.h>
# include <stdlib.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;
char	*get_next_line(int fd);
ssize_t	ft_read(int fd, char *buffer);
char	*ft_strdup(const char *s1);
int		ft_lstadd_back(t_list **lst, void *content);
void	ft_delone(t_list **lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));

#endif
