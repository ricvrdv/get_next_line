/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:02:44 by rjesus-d          #+#    #+#             */
/*   Updated: 2024/12/04 18:30:55 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static ssize_t	read_line(int fd, char **saved);
static char		*get_line(char **saved);

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*line;
	ssize_t		bytes_read;

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
		bytes_read = read_line(fd, &saved);
		if (bytes_read == 0 && saved && *saved)
		{
			line = saved;
			saved = NULL;
			return (line);
		}
		if (bytes_read == 0 && (!saved || !*saved))
		{
			free(saved);
			saved = NULL;
			return (NULL);
		}
		if (bytes_read < 0)
		{
			free(saved);
			saved = NULL;
			return (NULL);
		}
	}
	line = get_line(&saved);
	return (line);
}

static ssize_t	read_line(int fd, char **saved)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		*saved = ft_strjoin(*saved, buffer);
	}
	return (bytes_read);
}

static char	*get_line(char **saved)
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
		temp = ft_substr(*saved, len, ft_strlen(*saved) - len);
		free(*saved);
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

	buffer = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (buffer == NULL)
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

/*
#include <stdio.h>
#include <fcntl.h>

int	main()
{
	int		fd;
	char	*line;

	fd = open("test1.txt", O_RDONLY);
	while((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
*/
