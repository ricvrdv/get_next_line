char	*get_next_line(int fd)
{
	static char	*file;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	file = ft_read_file(fd, file);
	if (!file)
		return (NULL);
	line = ft_new_line(file);

}

char	*ft_read_file(int fd, char *file)
{
	char	*buffer;
	char	*temp;
	ssize_t	bytes_read;

	if (!file)
		file = ft_strdup("");
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
	{
		free(file);
		return (NULL);
	}
	bytes_read = 1;
	while (!ft_strchr(file, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(file);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(file, buffer);
		if (!temp)
		{
			free(buffer);
			free(file);
			return (NULL);
		}
		free(file);
		file = temp;
	}
	free(buffer);
	return (file);
}

char	*ft_new_line(char *file)
{
	char 	*line;
	size_t	i;

	if (!file || !*file)
		return (NULL);
	i = 0;
	while (file[i] != '\n' && file[i] != '\0')
		i++;
	line = ft_calloc(sizeof(char), (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (file[i] != '\n' && file[i] != '\0')
	{
		line[i] = file[i];
		i++;
	}
	if (file[i] == '\n')
		len[