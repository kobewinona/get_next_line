/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:09:12 by dklimkin          #+#    #+#             */
/*   Updated: 2023/09/26 13:09:13 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	handle_buffer(t_list **head, t_list **current, char *buffer)
{
	char	*content;

	content = ft_strdup(buffer);
	if (!content)
		ft_lstclear(head, free);
	ft_lstadd_back(head, content);
	if (!(*current))
		*current = *head;
	else
		*current = (*current)->next;
}

static char	*create_line_str(t_list **head, size_t line_len)
{
	char	*line_str;
	t_list	*current;
	size_t	i;
	size_t	j;

	line_str = (char *)malloc((line_len + 1) * sizeof(char));
	if (!line_str)
		return (NULL);
	current = *head;
	i = 0;
	while (i < line_len && current)
	{
		j = 0;
		while (current && current->content[j] && i < line_len)
		{
			line_str[i++] = current->content[j];
			if (current->content[j++] == '\n')
				break ;
		}
		ft_delone(&current, free);
		if (line_str[i - 1] == '\n')
			break ;
	}
	line_str[i] = '\0';
	*head = current;
	return (line_str);
}

static char	*handle_chunk(t_list **head, t_list **current, size_t *line_len)
{
	char	*new_line;
	ssize_t	i;

	new_line = NULL;
	i = 0;
	while ((*current)->content && (*current)->content[i] != '\0')
	{
		if ((*current)->content[i] == '\n')
		{
			new_line = &((*current)->content[i]);
			break ;
		}
		i++;
	}
	if (!new_line)
	{
		*line_len += i;
		return (NULL);
	}
	*line_len += (i + 1);
	if (*(new_line + 1) != '\0')
		ft_lstadd_back(current, ft_strdup(new_line + 1));
	return (create_line_str(head, *line_len));
}

static char	*extract_line(int fd, char *buffer)
{
	static t_list	*head;
	t_list			*current;
	ssize_t			bytes_read;
	char			*line_str;
	size_t			line_len;

	current = head;
	line_len = 0;
	if (head && head->content)
	{
		line_str = handle_chunk(&head, &current, &line_len);
		if (line_str)
			return (line_str);
	}
	bytes_read = ft_read(fd, buffer);
	while (bytes_read > 0)
	{
		handle_buffer(&head, &current, buffer);
		line_str = handle_chunk(&head, &current, &line_len);
		if (line_str)
			return (line_str);
		bytes_read = ft_read(fd, buffer);
	}
	if (bytes_read == 0 && head && head->content)
		return (create_line_str(&head, line_len));
	return (NULL);
}

char	*get_next_line(int fd)
{
	char	*buffer;
	char	*res_str;

	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	res_str = extract_line(fd, buffer);
	if (!res_str)
	{
		free(buffer);
		return (NULL);
	}
	free(buffer);
	return (res_str);
}
