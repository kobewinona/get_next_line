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

static char	*create_read_line_str(t_list **head, size_t read_line_len)
{
	char	*read_line_str;
	t_list 	*temp;
	t_list	*current;
	size_t	i;
	size_t	j;

	read_line_str = (char *)malloc((read_line_len + 1) * sizeof(char));
	if (!read_line_str)
		return (NULL);
	current = *head;
	i = 0;
	while (i < read_line_len && current)
	{
		j = 0;
		while (current->content[j] && i < read_line_len)
		{
		    read_line_str[i++] = current->content[j];
		    if (current->content[j] == '\n')
		        break;
		    j++;
		}
		temp = current;
		current = current->next;
		free(temp->content);
		free(temp);
		if (read_line_str[i-1] == '\n')
			break;
	}
	read_line_str[i] = '\0';
	*head = current;
	return (read_line_str);
}

static char	*extract_line_if_exists(t_list **head, t_list **current, size_t *read_line_len)
{
	char	*new_line;
	char	*read_line_str;

	new_line = ft_strchr((*current)->content, '\n');
	if (!new_line)
	{
		*read_line_len += ft_strlen((*current)->content);
		return (NULL);
	}
	*read_line_len += (new_line - (*current)->content) + 1;
	if (*(new_line + 1) != '\0')
		ft_lstadd_back(current, ft_strdup(new_line + 1));
	read_line_str = create_read_line_str(head, *read_line_len);
	return (read_line_str);
}

static ssize_t	read_fd(int fd, char *buffer)
{
	ssize_t	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read > 0)
		buffer[bytes_read] = '\0';
	else
		free(buffer);
	return (bytes_read);
}

static void handle_buffer(t_list **head, t_list **current, char *buffer, size_t *read_line_len)
{
	ft_lstadd_back(head, ft_strdup(buffer));
	if (!*current)
		*current = *head;
	else
		*current = (*current)->next;
	*read_line_len += ft_strlen(buffer);
}

static char	*find_new_line(int fd, char *buffer)
{
	static t_list	*head;
	t_list			*current;
	ssize_t			bytes_read;
	char			*read_line_str;
	size_t			read_line_len;

	current = head;
	read_line_len = 0;
	if (head)
	{
		read_line_str = extract_line_if_exists(&head, &current, &read_line_len);
		if (read_line_str)
			return (read_line_str);
	}
	bytes_read = read_fd(fd, buffer);
	while (bytes_read > 0)
	{
		handle_buffer(&head, &current, buffer, &read_line_len);
		read_line_str = extract_line_if_exists(&head, &current, &read_line_len);
		if (read_line_str)
			return (read_line_str);
		bytes_read = read_fd(fd, buffer);
	}
	if (bytes_read == 0 && head->content)
	{
		read_line_str = create_read_line_str(&head, read_line_len);
		return (read_line_str);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char			*buffer;

	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	buffer[BUFFER_SIZE] = '\0';
	return (find_new_line(fd, buffer));
}