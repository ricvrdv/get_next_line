/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: applecore <applecore@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:02:44 by rjesus-d          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/12/10 15:35:05 by rjesus-d         ###   ########.fr       */
=======
/*   Updated: 2024/12/06 00:11:29 by applecore        ###   ########.fr       */
>>>>>>> 8564bd1d83cf78dec721848e9649c4e958c21f08
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
<<<<<<< HEAD
		if (bytes_read == 0 && saved && *saved)
			return (line = saved, saved = NULL, line);
		if (bytes_read == 0 && (!saved || !*saved))
			return (free(saved), saved = NULL, NULL);
=======
		if (bytes_read == 0 && saved && *saved)// EOF with remaining data
		{
			line = saved;// Return the remaining data
			saved = NULL;// Reset static variable
			return (line);// Return remaining data before EOF
		}
		if (bytes_read == 0 && (!saved || !*saved)) // EOF with no data
		{
			free(saved);// Free memory if it exists
			saved = NULL;// Reset saved
			return (NULL);// Return NULL to signal EOF
		}
>>>>>>> 8564bd1d83cf78dec721848e9649c4e958c21f08
		if (bytes_read < 0)
			return (free(saved), saved = NULL, NULL);
	}
	line = get_line(&saved);
	return (line);
}

static ssize_t	read_line(int fd, char **saved)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		*saved = ft_strjoin(*saved, buffer);
	}
	free(buffer);
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

#include <stdio.h>
#include <fcntl.h>

int	main()
{
	int		fd;
	char	*line;

	//fd = open("animaniac.txt", O_RDONLY);
	//while ((line = get_next_line(fd)))
	//{
	//	printf("%s", line);
	//	free(line);
	//}
	//close(fd);

	//fd = open("ghosts.txt", O_RDONLY);
	//while ((line = get_next_line(fd)))
	//{
	//	printf("%s", line);
	//	free(line);
	//}
	//close(fd);

	fd = open("big_line_with_nl", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}