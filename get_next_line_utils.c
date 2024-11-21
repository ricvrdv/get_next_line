#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s != '\0')
		len++;
	return (len);
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*sjoint;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	size_t	j;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	sjoint = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!sjoint)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		sjoint[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		sjoint[i + j] = s2[j];
		j++;
	}
	sjoint[i + j] = '\0';
	return (sjoint);
}

char	*ft_strchr(const char *s, int c)
{
	char	ch;

	ch = (char)c;
	while (*s != '\0')
	{
		if (*s == ch)
			return ((char *)s);
		s++;
	}
	if (ch == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	substring = (char *)malloc(sizeof(char) * (len + 1));
	if (!substring)
		return (NULL);
	i = 0;
	while (s[start + i] != '\0' && i < len)
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}