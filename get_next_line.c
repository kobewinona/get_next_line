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

static char	*handle_error(t_list **head, char *buff)
{
	if (*head)
	{
		while (*head)
			ft_delone(head, free);
	}
	if (buff)
		free(buff);
	return (NULL);
}

static char	*create_line_str(t_list **head, size_t len)
{
	t_list	*current;
	char	*line_str;
	size_t	i;
	size_t	j;

	current = *head;
	line_str = (char *)malloc((len + 1) * sizeof(char));
	if (!line_str)
		return (handle_error(head, NULL));
	i = 0;
	while (i < len && current)
	{
		j = 0;
		while (current->content[j] && i < len)
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

static int	handle_buff(t_list **head, char *buff)
{
	t_list	*current;

	current = *head;
	if (!ft_lstadd_back(head, buff))
	{
		while (*head)
			ft_delone(head, free);
		if (buff)
			free(buff);
		return (0);
	}
	if (!current)
		current = *head;
	else
		current = current->next;
	return (1);
}

static char	*read_file(int fd, char *buff, t_list **head, size_t *len)
{
	ssize_t	bytes_read;
	char	*nl;

	bytes_read = ft_read(fd, buff);
	while (bytes_read > 0)
	{
		if (handle_buff(head, buff) == 0)
			return (NULL);
		nl = find_nl(buff, len);
		if (nl)
		{
			if (*(nl + 1) != '\0' && !ft_lstadd_back(head, (nl + 1)))
				return (handle_error(head, buff));
			free(buff);
			return (create_line_str(head, *len));
		}
		bytes_read = ft_read(fd, buff);
	}
	free(buff);
	if (bytes_read == 0 && *head && (*head)->content)
		return (create_line_str(head, *len));
	if (bytes_read < 0 && *head)
		ft_delone(head, free);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_list	*head;
	char			*nl;
	char			*buff;
	size_t			len;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	len = 0;
	if (head && head->content)
	{
		nl = find_nl(head->content, &len);
		if (nl)
		{
			if (*(nl + 1) != '\0')
			{
				if (!ft_lstadd_back(&head, (nl + 1)))
					return (handle_error(&head, NULL));
			}
			return (create_line_str(&head, len));
		}
	}
	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (handle_error(&head, buff));
	return (read_file(fd, buff, &head, &len));
}
