/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:17:55 by dklimkin          #+#    #+#             */
/*   Updated: 2023/09/26 13:17:55 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	ft_read(int fd, char *buffer)
{
	ssize_t	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read > 0 && bytes_read <= BUFFER_SIZE)
		buffer[bytes_read] = '\0';
	return (bytes_read);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	s1_len;
	size_t	i;

	s1_len = 0;
	while (s1 && s1[s1_len] != '\0')
		s1_len++;
	s2 = (char *)malloc((s1_len + 1) * sizeof(char));
	// s2 = (char *)malloc(-1);
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

int	ft_lstadd_back(t_list **lst, void *content)
{
	t_list	*new;
	t_list	*current;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (0);
	else
	{
		new->content = content;
		new->next = (NULL);
	}
	if (*lst == NULL)
		*lst = new;
	else
	{
		current = *lst;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (1);
}

void	ft_delone(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	temp = *lst;
	*lst = (*lst)->next;
	if (temp)
	{
		if (del && temp && temp->content)
			del(temp->content);
		free(temp);
	}
	temp = NULL;
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	if (lst)
		next = *lst;
	if (del)
	{
		while (next)
		{
			next = next->next;
			if (*lst && del)
			{
				if ((*lst)->content)
				{
					del((*lst)->content);
					(*lst)->content = NULL;
				}
				del(*lst);
			}
			*lst = next;
		}
	}
}
