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

// WITH ALL THE NULLS

// static char	*create_line_str(t_list **head, size_t line_len)
// {
// 	char	*line_str;
// 	t_list	*current;
// 	size_t	i;
// 	size_t	j;

// 	current = *head;
// 	line_str = (char *)malloc((line_len + 1) * sizeof(char));
// 	if (!line_str)
// 		return (NULL);
// 	i = 0;
// 	while (i < line_len && current)
// 	{
// 		j = 0;
// 		while (current && current->content[j] && i < line_len)
// 		{
// 			line_str[i++] = current->content[j];
// 			if (current->content[j++] == '\n')
// 				break ;
// 		}
// 		ft_delone(&current, free);
// 		// if (i > 0 && (*line_str)[i - 1] == '\n')
// 		// 	break ;
// 	}
// 	line_str[i] = '\0';
// 	*head = current;
// 	return (line_str);
// }

// static char	*find_new_line(char *buffer, size_t *line_len)
// {
// 	ssize_t	i;

// 	i = 0;
// 	while (buffer && buffer[i] != '\0')
// 	{
// 		if (buffer[i] == '\n')
// 		{
// 			*line_len += i + 1;
// 			return (&buffer[i]);
// 		}
// 		i++;
// 	}
// 	*line_len += i;
// 	return (NULL);
// }

// // static void	handle_buffer(t_list **head, char *buffer)
// // {
// // 	char	*content;
// // 	t_list	*current;

// // 	current = *head;
// // 	content = ft_strdup(buffer);
// // 	if (!content)
// // 		ft_lstclear(head, free);
// // 	ft_lstadd_back(head, content);
// // 	if (!current)
// // 		current = *head;
// // 	else
// // 		current = current->next;
// // }

// // static char *handle_new_line(t_list **head, size_t line_len)
// // {
// // 	char	*line_str;

// // 	line_str = (char *)malloc((line_len + 1) * sizeof(char));
// // 	if (!line_str)
// // 	{
// // 		ft_lstclear(head, free);
// // 		return (NULL);
// // 	}
// // 	create_line_str(head, &line_str, line_len);
// // 	return (line_str);
// // }

// static char	*read_file(int fd, t_list **head, size_t *line_len)
// {
// 	t_list	*current;
// 	ssize_t bytes_read;
// 	char	*buffer;
// 	char	*new_line;
// 	char	*stash;
// 	char	*content;
// 	char	*line_str;

// 	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
// 	if (!buffer)
// 		return (NULL);
// 	bytes_read = 0;
// 	bytes_read = ft_read(fd, buffer);
// 	// printf("1 bytes read %zd, buffer |%s|\n", bytes_read, buffer);
// 	while (bytes_read > 0)
// 	{
// 		current = *head;
// 		content = ft_strdup(buffer);
// 		if (!content)
// 		{
// 			free(buffer);
// 			ft_lstclear(head, free);
// 			return (NULL);
// 		}
// 		// ft_lstadd_back(head, content);
// 		if (!ft_lstadd_back(head, content))
// 		{
// 			ft_lstclear(head, free);
// 			free(buffer);
// 			return (NULL);
// 		}
// 		if (!current)
// 			current = *head;
// 		else
// 			current = current->next;
// 		new_line = find_new_line(buffer, line_len);
// 		// printf("new_line |%s|\n", new_line);
// 		if (new_line)
// 		{
// 			if (*(new_line + 1) != '\0')
// 			{
// 				stash = ft_strdup((new_line + 1));
// 				// printf("stash |%s|\n", stash);
// 				if (!stash)
// 				{
// 					free(buffer);
// 					ft_lstclear(head, free);
// 					return (NULL);
// 				}
// 				// ft_lstadd_back(head, stash);
// 				if (!ft_lstadd_back(head, stash))
// 				{
// 					free(buffer);
// 					ft_lstclear(head, free);
// 					return (NULL);
// 				}
// 			}
// 			free(buffer);
// 			line_str = create_line_str(head, *line_len);
// 			if (!line_str)
// 			{
// 				// free(buffer);
// 				ft_lstclear(head, free);
// 				return (NULL);
// 			}
// 			return (line_str);
// 		}
// 		bytes_read = ft_read(fd, buffer);
// 		// printf("2 bytes read %zd, buffer |%s|\n", bytes_read, buffer);
// 	}
// 	// printf("here\n");
// 	free(buffer);
// 	if (*head && (*head)->content)
// 	{
// 		// printf("here\n");
// 		// return (handle_new_line(head, *line_len));
// 		line_str = create_line_str(head, *line_len);
// 		if (!line_str)
// 		{
// 			ft_lstclear(head, free);
// 			return (NULL);
// 		}
// 		return (line_str);
// 	}
// 	if (bytes_read < 0)
// 	{
// 		ft_lstclear(head, free);
// 		return (NULL);
// 	}
// 	return (NULL);
// }

// char	*get_next_line(int fd)
// {
// 	static t_list	*head;
// 	char			*new_line;
// 	char			*line_str;
// 	char			*stash;
// 	size_t			line_len;

// 	// if (fd < 0)
// 	// 	return (NULL);
// 	if (fd < 0 || BUFFER_SIZE < 1)
// 	{
// 		if (head)
// 			ft_delone(&head, free);
// 		return (NULL);
// 	}
// 	line_len = 0;
// 	if (head && head->content)
// 	{
// 		new_line = find_new_line(head->content, &line_len);
// 		if (new_line)
// 		{
// 			if (*(new_line + 1) != '\0')
// 			{
// 				stash = ft_strdup((new_line + 1));
// 				if (!stash)
// 				{
// 					ft_lstclear(&head, free);
// 					return (NULL);
// 				}
// 				// ft_lstadd_back(&head, stash);
// 				if (!ft_lstadd_back(&head, stash))
// 				{
// 					ft_lstclear(&head, free);
// 					return (NULL);
// 				}
// 			}
// 			line_str = create_line_str(&head, line_len);
// 			if (!line_str)
// 			{
// 				ft_lstclear(&head, free);
// 				return (NULL);
// 			}
// 			return (line_str);
// 		}
// 	}
// 	line_str = read_file(fd, &head, &line_len);
// 	// printf("head content |%s|\n", head->content);
// 	if (!line_str)
// 	{
// 		ft_lstclear(&head, free);
// 		return (NULL);
// 	}
// 	return (line_str);
// }


// DON'T KNOW WHAT'S THIS VERSION

// static void	handle_buffer(t_list **head, t_list **current, char *buffer)
// {
// 	char	*content;

// 	content = ft_strdup(buffer);
// 	if (!content)
// 		ft_lstclear(head, free);
// 	ft_lstadd_back(head, content);
// 	if (!(*current))
// 		*current = *head;
// 	else
// 		*current = (*current)->next;
// }

// static char	*create_line_str(t_list **head, size_t line_len)
// {
// 	char	*line_str;
// 	t_list	*current;
// 	size_t	i;
// 	size_t	j;

// 	line_str = (char *)malloc((line_len + 1) * sizeof(char));
// 	if (!line_str)
// 		return (NULL);
// 	current = *head;
// 	i = 0;
// 	while (i < line_len && current)
// 	{
// 		j = 0;
// 		while (current && current->content[j] && i < line_len)
// 		{
// 			line_str[i++] = current->content[j];
// 			if (current->content[j++] == '\n')
// 				break ;
// 		}
// 		ft_delone(&current, free);
// 		if (i > 0 && line_str[i - 1] == '\n')
// 			break ;
// 	}
// 	line_str[i] = '\0';
// 	*head = current;
// 	return (line_str);
// }

// static char	*handle_chunk(t_list **head, t_list **current, size_t *line_len)
// {
// 	char	*new_line;
// 	ssize_t	i;

// 	new_line = NULL;
// 	i = 0;
// 	while (*current && (*current)->content[i] != '\0')
// 	{
// 		if ((*current)->content[i] == '\n')
// 		{
// 			new_line = &((*current)->content[i]);
// 			break ;
// 		}
// 		i++;
// 	}
// 	if (!new_line)
// 	{
// 		*line_len += i;
// 		return (NULL);
// 	}
// 	*line_len += (i + 1);
// 	if (*(new_line + 1) != '\0')
// 		ft_lstadd_back(current, ft_strdup(new_line + 1));
// 	return (create_line_str(head, *line_len));
// }

// static char	*extract_line(int fd, char *buffer)
// {
// 	static t_list	*head;
// 	t_list			*current;
// 	ssize_t			bytes_read;
// 	char			*line_str;
// 	size_t			line_len;

// 	current = head;
// 	line_len = 0;
// 	if (head && head->content)
// 	{
// 		line_str = handle_chunk(&head, &current, &line_len);
// 		if (line_str)
// 			return (line_str);
// 	}
// 	bytes_read = ft_read(fd, buffer);
// 	while (bytes_read > 0)
// 	{
// 		handle_buffer(&head, &current, buffer);
// 		line_str = handle_chunk(&head, &current, &line_len);
// 		if (line_str)
// 			return (line_str);
// 		bytes_read = ft_read(fd, buffer);
// 	}
// 	if (bytes_read == 0 && head && head->content)
// 	{
// 		line_str = create_line_str(&head, line_len);
// 		ft_lstclear(&head, free);
// 		return (line_str);
// 	}
// 	if (bytes_read < 0)
// 		ft_lstclear(&head, free);
// 	return (NULL);
// }

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
		if (i > 0 && line_str[i - 1] == '\n')
			break ;
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

static void	handle_buffer(t_list **head, char *buffer)
{
	char	*content;
	t_list	*current;

	current = *head;
	content = ft_strdup(buffer);
	if (!content)
		ft_lstclear(head, free);
	ft_lstadd_back(head, content);
	if (!current)
		current = *head;
	else
		current = current->next;
}

static char	*read_file(int fd, t_list **head, char *buffer, size_t *line_len)
{
	char	*new_line;
	ssize_t	bytes_read;

	bytes_read = ft_read(fd, buffer);
	while (bytes_read > 0)
	{
		handle_buffer(head, buffer);
		new_line = find_new_line(buffer, line_len);
		if (new_line)
			return (new_line);
		bytes_read = ft_read(fd, buffer);
	}
	if (bytes_read < 0)
		ft_lstclear(head, free);
	return (NULL);
}

static char	*extract_line(int fd, char *buffer)
{
	static t_list	*head;
	t_list			*current;
	char			*line_str;
	size_t			line_len;
	char			*new_line;

	current = head;
	line_len = 0;
	if (head && head->content)
	{
		new_line = find_new_line(head->content, &line_len);
		if (new_line)
		{

			if (*(new_line + 1) != '\0')
				ft_lstadd_back(&head, ft_strdup(new_line + 1));
			line_str = create_line_str(&head, line_len);
			return (line_str);
		}
	}
	new_line = read_file(fd, &head, buffer, &line_len);
	if (new_line)
	{
		line_str = create_line_str(&head, line_len);
		ft_lstclear(&head, free);
		if (*(new_line + 1) != '\0')
			ft_lstadd_back(&head, ft_strdup(new_line + 1));
		return (line_str);
	}
	if (head && head->content)
	{
		line_str = create_line_str(&head, line_len);
		ft_lstclear(&head, free);
		return (line_str);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char	*buffer;
	char	*res_str;

	if (fd < 0 || BUFFER_SIZE < 1)
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
