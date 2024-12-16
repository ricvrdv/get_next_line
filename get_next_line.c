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

// Reads from fd and update the 'saved' buffer
static ssize_t	read_file(int fd, char **saved);
// Extracts the next line from 'saved' and update it
static char		*extract_and_update_line(char **saved);

char	*get_next_line(int fd)
{
	static char	*saved; // it maintains state across function calls
	char		*line; // to store the line to return
	ssize_t		bytes_read; // bytes read from fd

	line = NULL;
	// Checking for invalid fd and BUFFER_SIZE
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	// Initializing 'saved' if it is the first call
	if (!saved)
	{
		saved = ft_strdup("");
		if (!saved)
			return (NULL);
	}
	// Keep reading until a '\n' is found
	while (!ft_strchr(saved, '\n'))
	{
		bytes_read = read_file(fd, &saved);
		// Handle read errors
		if (bytes_read < 0)
			return (free_and_reset(&saved), NULL);
		// If EOF is reached but there is leftover data
		if (bytes_read == 0 && saved && *saved)
			return (line = saved, saved = NULL, line);
		// If EOF is reached and 'saved' is empty
		if (bytes_read == 0 && (!saved || !*saved))
			return (free_and_reset(&saved), NULL);
	}
	// Extracting next line from 'saved'
	line = extract_and_update_line(&saved);
	return (line);
}

static ssize_t	read_file(int fd, char **saved)
{
	char	*buffer; // temporary buffer for reading
	char	*temp; // temporary pointer for joining strings
	ssize_t	bytes_read; 

	// Allocating memory for 'buffer' + 1 for '\0'
	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (-1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	// If no data is read or an error occurs
	if (bytes_read <= 0)
		free_and_reset(&buffer);
	// If data is read successfully
	if (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		// Appending 'buffer' to 'saved'
		temp = ft_strjoin(*saved, buffer);
		if (!temp)
			return (*saved = NULL, -1);
		*saved = temp; // updates 'saved' with new content
		buffer = NULL;
	}
	return (bytes_read);
}

static char	*extract_and_update_line(char **saved)
{
	char	*new_line; // pointer to the first '\n'
	char	*line; // the line to return
	char	*temp; // temporary pointer for updating 'saved'
	size_t	len; // length of the line to extract

	// Finding the first '\n'
	new_line = ft_strchr(*saved, '\n');
	if (new_line) // if found
	{
		// Calculating the length of the line to extract 
		// using pointer arithmetics, + 1 to include '\n'
		len = new_line - *saved + 1;
		// Extracting the line to return
		line = ft_substr(*saved, 0, len);
		if (!line)
			return (free_and_reset(&*saved), NULL);
		// Getting the remaining content
		temp = ft_substr(*saved, len, ft_strlen(*saved) - len);
		if (!temp)
			return (free_and_reset(&*saved), free_and_reset(&line), NULL);
		free_and_reset(&*saved);
		*saved = temp; // updates 'saved' with the remaining content
	}
	else // if '\n' is not found
	{
		line = *saved; // to return the entire 'saved' buffer
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
