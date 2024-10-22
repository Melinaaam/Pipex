/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:09:35 by memotyle          #+#    #+#             */
/*   Updated: 2024/10/21 13:20:42 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_buffer(char **buffer)
{
	if (*buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
}

static char	*get_line(char **buffer)
{
	char	*line;
	char	*rest;
	int		i;

	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	if ((*buffer)[i] == '\n')
	{
		line = ft_strndup(*buffer, i + 1);
		rest = ft_strdup(*buffer + i + 1);
		if (!line || !rest)
			return (free_buffer(buffer), NULL);
		free_buffer(buffer);
		*buffer = rest;
		if ((*buffer)[0] == '\0')
			free_buffer(buffer);
	}
	else
	{
		line = ft_strdup(*buffer);
		free_buffer(buffer);
	}
	return (line);
}

static int	read_file(int fd, char **buffer)
{
	char	*read_buffer;
	int		bytes_read;

	read_buffer = malloc(BUFFER_SIZE + 1);
	if (!read_buffer)
		return (-1);
	bytes_read = read(fd, read_buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		read_buffer[bytes_read] = '\0';
		if (!*buffer)
			*buffer = ft_strdup(read_buffer);
		else
			*buffer = ft_strjoin(*buffer, read_buffer);
		if (!*buffer)
			return (free(read_buffer), -1);
		if (ft_strchr(read_buffer, '\n'))
			break ;
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
	}
	return (free(read_buffer), bytes_read);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = read_file(fd, &buffer);
	if (bytes_read < 0)
		return (free_buffer(&buffer), NULL);
	if (bytes_read == 0 && !buffer)
		return (NULL);
	return (get_line(&buffer));
}
