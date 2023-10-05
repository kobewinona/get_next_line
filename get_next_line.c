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

static char	*create_line_str(t_list **head, size_t line_len)
{
	char	*line_str;
	t_list	*temp;
	t_list	*current;
	size_t	i;
	size_t	j;

	printf("line_len %zd\n", line_len);
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
			if (current->content[j] == '\n')
				break ;
			j++;
		}
		temp = current;
		current = current->next;
		free(temp->content);
		free(temp);
		if (line_str[i - 1] == '\n')
			break ;
	}
	line_str[i] = '\0';
	*head = current;
	return (line_str);
}

static char	*extract_line(t_list **head, t_list **current, size_t *line_len)
{
	char	*new_line;
	char	*line_str;
	char	*stash;

	new_line = ft_strchr((*current)->content, '\n');
	if (!new_line)
	{
		*line_len += ft_strlen((*current)->content);
		return (NULL);
	}
	*line_len += (new_line - (*current)->content) + 1;
	if (*(new_line + 1) != '\0')
	{
		stash = ft_strdup(new_line + 1);
		if (!stash)
			ft_lstclear(head, free);
		ft_lstadd_back(current, stash);
	}
	line_str = create_line_str(head, *line_len);
	if (!line_str)
		ft_lstclear(head, free);
	return (line_str);
}

static ssize_t	read_fd(int fd, char *buffer)
{
	ssize_t	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read > 0 && bytes_read < BUFFER_SIZE)
		buffer[bytes_read] = '\0';
	return (bytes_read);
}

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

static char	*find_new_line(int fd, char *buffer)
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
		line_str = extract_line(&head, &current, &line_len);
		if (line_str)
			return (line_str);
	}
	bytes_read = read_fd(fd, buffer);
	while (bytes_read > 0)
	{
		handle_buffer(&head, &current, buffer);
		line_str = extract_line(&head, &current, &line_len);
		if (line_str)
			return (line_str);
		bytes_read = read_fd(fd, buffer);
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
	res_str = find_new_line(fd, buffer);
	free(buffer);
	return (res_str);
}
