/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:10:28 by rjesus-d          #+#    #+#             */
/*   Updated: 2024/12/04 17:49:23 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (*s && s[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin(char *s1, const char *s2)
{
	char	*sjoint;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	sjoint = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!sjoint)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		sjoint[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		sjoint[i + j] = s2[j];
		j++;
	}
	sjoint[i + j] = '\0';
	free(s1);
	return (sjoint);
}

char	*ft_substr(char *s, size_t start, size_t len)
{
	char	*substring;
	size_t	s_len;
	size_t	i;

	s_len = ft_strlen(s);
	if (!s || start >= s_len)
		return (NULL);
	if (len > s_len - start)
		len = s_len - start;
	substring = (char *)malloc(sizeof(char) * (len + 1));
	if (!substring)
		return (NULL);
	i = 0;
	while (s[start] && i < len)
		substring[i++] = s[start++];
	substring[i] = '\0';
	return (substring);
}
