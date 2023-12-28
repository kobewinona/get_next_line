/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_internal.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:28:43 by dklimkin          #+#    #+#             */
/*   Updated: 2023/12/11 20:28:44 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBGNL_INTERNAL_H
# define LIBGNL_INTERNAL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
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
char	*find_nl(char *buff, size_t *len);
ssize_t	ft_read(int fd, char *buffer);
char	*ftm_strdup(const char *s1);
int		ftm_lstadd_back(t_list **lst, void *content);
void	ft_delone(t_list **lst, void (*del)(void *));

#endif
