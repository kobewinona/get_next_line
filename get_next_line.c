/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:26:42 by dklimkin          #+#    #+#             */
/*   Updated: 2023/10/11 11:26:44 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	handle_error(t_list **head, char *buffer, char *content)
{
	if (!content)
	{
		ft_lstclear(head, free);
		*head = NULL;
		if (buffer)
			free(buffer);
		return (1);
	}
	return (0);
}

static char	*create_line_str(t_list **head, size_t line_len)
{
	t_list	*current;
	char	*line_str;
	size_t	i;
	size_t	j;

	current = *head;
	line_str = (char *)malloc((line_len + 1) * sizeof(char));
	if (!line_str)
		return (NULL);
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
	}
	line_str[i] = '\0';
	*head = current;
	return (line_str);
}

static char	*find_new_line(t_list **head, char *buffer, size_t *line_len)
{
	ssize_t	i;
	char	*stash;

	i = 0;
	while (buffer && buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
		{
			if (buffer[i + 1] != '\0')
			{
				stash = ft_strdup(&(buffer[i + 1]));
				if (handle_error(head, buffer, stash))
					return (NULL);
				ft_lstadd_back(head, stash);
			}
			*line_len += i + 1;
			return (&buffer[i]);
		}
		i++;
	}
	*line_len += i;
	return (NULL);
}

static int	handle_buffer(t_list **head, char *buffer)
{
	char	*content;
	t_list	*current;

	current = *head;
	content = ft_strdup(buffer);
	if (handle_error(head, buffer, content))
		return (0);
	ft_lstadd_back(head, content);
	if (!current)
		current = *head;
	else
		current = current->next;
	return (1);
}

static char	*read_file(int fd, char *buffer, t_list **head, size_t *line_len)
{
	ssize_t	bytes_read;
	char	*new_line;

	bytes_read = ft_read(fd, buffer);
	if (bytes_read > 0)
		buffer[bytes_read] = '\0';
	while (bytes_read > 0)
	{
		if (!handle_buffer(head, buffer))
			return (NULL);
		new_line = find_new_line(head, buffer, line_len);
		if (new_line)
			return (create_line_str(head, *line_len));
		bytes_read = ft_read(fd, buffer);
	}
	if (bytes_read == 0 && *head && (*head)->content)
		return (create_line_str(head, *line_len));
	if (bytes_read < 0 && head)
		ft_lstclear(head, free);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_list	*head;
	char			*new_line;
	char			*line_str;
	char			*buffer;
	size_t			line_len;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line_len = 0;
	if (head && head->content)
	{
		new_line = find_new_line(&head, head->content, &line_len);
		if (new_line)
			return (create_line_str(&head, line_len));
	}
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (handle_error(&head, buffer, buffer))
		return (NULL);
	line_str = read_file(fd, buffer, &head, &line_len);
	if (handle_error(&head, buffer, line_str))
		return (NULL);
	free(buffer);
	return (line_str);
}
