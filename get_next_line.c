/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:02:44 by rjesus-d          #+#    #+#             */
/*   Updated: 2024/12/16 18:47:23 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static ssize_t	read_file(int fd, char **saved);
static char		*extract_and_update_line(char **saved);

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*line;
	ssize_t		bytes_read;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!saved)
	{
		saved = ft_strdup("");
		if (!saved)
			return (NULL);
	}
	while (!ft_strchr(saved, '\n'))
	{
		bytes_read = read_file(fd, &saved);
		if (bytes_read < 0)
			return (free_and_reset(&saved), NULL);
		if (bytes_read == 0 && saved && *saved)
			return (line = saved, saved = NULL, line);
		if (bytes_read == 0 && (!saved || !*saved))
			return (free_and_reset(&saved), NULL);
	}
	line = extract_and_update_line(&saved);
	return (line);
}

static ssize_t	read_file(int fd, char **saved)
{
	char	*buffer;
	char	*temp;
	ssize_t	bytes_read;

	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (-1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
		free_and_reset(&buffer);
	if (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(*saved, buffer);
		if (!temp)
			return (*saved = NULL, -1);
		*saved = temp;
		buffer = NULL;
	}
	return (bytes_read);
}

static char	*extract_and_update_line(char **saved)
{
	char	*new_line;
	char	*line;
	char	*temp;
	size_t	len;

	new_line = ft_strchr(*saved, '\n');
	if (new_line)
	{
		len = new_line - *saved + 1;
		line = ft_substr(*saved, 0, len);
		if (!line)
			return (free_and_reset(&*saved), NULL);
		temp = ft_substr(*saved, len, ft_strlen(*saved) - len);
		if (!temp)
			return (free_and_reset(&*saved), free_and_reset(&line), NULL);
		free_and_reset(&*saved);
		*saved = temp;
	}
	else
	{
		line = *saved;
		*saved = NULL;
	}
	return (line);
}

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*buffer;

	if (!s)
		return (NULL);
	buffer = (char *)ft_calloc((ft_strlen(s) + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		buffer[i] = s[i];
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}

void	free_and_reset(char **buffer)
{
	if (buffer && *buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
}
/*
#include <stdio.h>
#include <fcntl.h>

int	main()
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening the file.");
		return (1);
	}
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
*/
