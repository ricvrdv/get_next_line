/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:02:44 by rjesus-d          #+#    #+#             */
/*   Updated: 2024/12/10 15:35:05 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static ssize_t	read_line(int fd, char **saved);
static char		*extract_line(char **saved);

char	*get_next_line(int fd)
{
	// 'saved' retains its value between function calls
	// used to store leftover data from previous reads
	static char	*saved;
	char		*line; // will hold the line to be returned
	ssize_t		bytes_read; // will store the number of bytes read from the file

	// Error check: if 'fd' is invalid or the buffer size is less than or equal to zero
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	// Initialization of 'saved' if it is not yet initialized
	if (!saved)
	{
		saved = ft_strdup(""); // 'saved' is set to an empty string
		if (!saved)
			return (NULL);
	}
	// Loop until newline found
	while (!ft_strchr(saved, '\n'))
	{
		bytes_read = read_line(fd, &saved); // reads data from the file into 'saved'
		// EOF check: if no more bytes are read and there is data in 'saved'
		// return that data as the line
		if (bytes_read == 0 && saved && *saved)
			return (line = saved, saved = NULL, line);
		// No more data: if no more bytes are read and 'saved' is empty
		// free it and return 'NULL'
		if (bytes_read == 0 && (!saved || !*saved))
			return (free(saved), saved = NULL, NULL);
		// Read error check
		if (bytes_read < 0)
			return (free(saved), saved = NULL, NULL);
	}
	line = extract_line(&saved); // extracts the next line from 'saved'
	return (line); // the extracted line is returned
}

static ssize_t	read_line(int fd, char **saved)
{
	char	*buffer; // buffer for reading data
	ssize_t	bytes_read; // to store the number of bytes read

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	// Reads up to 'BUFFER_SIZE' bytes from 'fd' into 'buffer'
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(buffer);
		return (-1);
	}
	else
	{
		buffer[bytes_read] = '\0';
		// Appending the newly read data to what is already in 'saved'
		*saved = ft_strjoin(*saved, buffer);
	}
	free(buffer);
	return (bytes_read);
}

static char	*extract_line(char **saved)
{
	char	*new_line;
	char	*line;
	char	*temp;
	size_t	len;

	// Find newline character
	new_line = ft_strchr(*saved, '\n');
	if (new_line)
	{
		// If a newline was found
		// calculate its position relative to the start of 'saved'
		len = new_line - *saved + 1;
		// Extract line substring
		line = ft_substr(*saved, 0, len);
		// Get remaining string
		temp = ft_substr(*saved, len, ft_strlen(*saved) - len);
		free(*saved); // free the old value of 'saved'
		*saved = temp; // update 'saved' with remaining string
	}
	// If no newline was found
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

#include <stdio.h>
#include <fcntl.h>

int	main()
{
	int		fd;
	char	*line;

	fd = open("animaniac.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);

	fd = open("ghosts.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);

	fd = open("big_line_with_nl", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
