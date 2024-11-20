char	*get_next_line(int fd)
{
	char	*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(left_c);
		free(buffer);
		left_c = NULL;
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = //FUNCTION TO FILL LINE
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	left_c = //FUNCTION TO HANDLE LEFTOVERS
	return (line);
}