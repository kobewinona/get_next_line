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
		if (*head)
		{
			ft_lstclear(head, free);
			*head = NULL;
		}
		if (buffer)
		{
			free(buffer);
			buffer = NULL;
		}
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

static char	*find_new_line(char *buffer, size_t *line_len)
{
	ssize_t	i;

	i = 0;
	while (buffer && buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
		{
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
	if (!content)
		return (0);
	if (!ft_lstadd_back(head, content))
	{
		free(content);
		return (0);
	}
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
	char	*stash;
	char	*line_str;

	bytes_read = ft_read(fd, buffer);
	while (bytes_read > 0)
	{
		if (!handle_buffer(head, buffer))
			return (NULL);
		new_line = find_new_line(buffer, line_len);
		if (new_line)
		{
			if (*(new_line + 1) != '\0')
			{
				stash = ft_strdup((new_line + 1));
				if (!stash)
					return (NULL);
				if (!ft_lstadd_back(head, stash))
				{
					free(stash);
					return (NULL);
				}
			}
			line_str = create_line_str(head, *line_len);
			if (!line_str)
				return (NULL);
			return (line_str);
		}
		bytes_read = ft_read(fd, buffer);
	}
	if (bytes_read == 0 && *head && (*head)->content)
	{
		line_str = create_line_str(head, *line_len);
		if (!line_str)
			return (NULL);
		return (line_str);
	}
	if (bytes_read < 0 && *head)
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
	char			*stash;

	line_str = NULL;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line_len = 0;
	if (head && head->content)
	{
		new_line = find_new_line(head->content, &line_len);
		if (new_line)
		{
			if (*(new_line + 1) != '\0')
			{
				stash = ft_strdup((new_line + 1));
				if (handle_error(&head, NULL, stash))
					return (NULL);
				if (!ft_lstadd_back(&head, stash))
				{
					free(stash);
					ft_lstclear(&head, free);
					return (NULL);
				}
			}
			line_str = create_line_str(&head, line_len);
			if (handle_error(&head, NULL, line_str))
				return (NULL);
			return (line_str);
		}
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
