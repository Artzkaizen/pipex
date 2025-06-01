/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuezeri  <chuezeri@student.42.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:12:50 by chuezeri          #+#    #+#             */
/*   Updated: 2025/06/01 12:39:23 by chuezeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > (size_t)-1 / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
		((char *)ptr)[i++] = 0;
	return (ptr);
}

static char	*ft_realloc(char *ptr, size_t new_size)
{
	size_t	i;
	char	*new_ptr;

	if (!new_size)
		return (NULL);
	if (!ptr)
		return ((char *)ft_calloc(new_size, sizeof(char)));
	new_ptr = (char *)ft_calloc(new_size, sizeof(char));
	if (!new_ptr)
		return (NULL);
	i = 0;
	while (ptr[i] && i < new_size)
	{
		new_ptr[i] = ptr[i];
		i++;
	}
	free(ptr);
	return (new_ptr);
}

static char	*parse_line(char *s, t_file *file, int realloc, int buff_size)
{
	int		len;

	len = 0;
	if (!file->bytes_read || !*s)
		return (file->line = NULL);
	if ((file->bytes_parsed) == buff_size)
		file->bytes_parsed = 0;
	while (++file->bytes_parsed < buff_size && s[len] && s[len] != '\n')
		len++;
	if (realloc)
	{
		file->line = ft_realloc(file->line, (len + file->line_len + 2));
		len += file->line_len;
	}
	else
	{
		file->line = (char *)ft_calloc(sizeof(char), (len + 2));
		if (!file->line)
			return (NULL);
	}
	file->line_len = ft_strlcat(file->line, s, (len + 2));
	return (file->line);
}

static int	is_empty(char *buffer, int size)
{
	int	i;

	i = 0;
	while (i < size && !buffer[i])
		i++;
	return (!buffer[i]);
}

char	*get_next_line(int fd)
{
	static t_file	file = {-1, 0, 0, 0, NULL};
	int				empty;
	static char		buffer[BUFFER_SIZE + 1];

	if (fd != -1 && BUFFER_SIZE > 0)
		file.fd = fd;
	else
		return (NULL);
	empty = is_empty(buffer, BUFFER_SIZE);
	if (empty)
		file.bytes_read = read(file.fd, buffer, BUFFER_SIZE);
	if (file.bytes_read == file.bytes_parsed || empty)
		file.bytes_parsed = 0;
	parse_line(&buffer[file.bytes_parsed], &file, 0, BUFFER_SIZE);
	while ((file.bytes_read == BUFFER_SIZE) && file.line
		&& file.line[file.line_len - 1] != '\n')
	{
		file.bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (file.bytes_read > 0)
			parse_line(buffer, &file, 1, BUFFER_SIZE);
	}
	return (file.line);
}
