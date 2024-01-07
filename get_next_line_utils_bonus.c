/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suminkwon <suminkwon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 22:58:34 by suminkwon         #+#    #+#             */
/*   Updated: 2024/01/04 23:00:20 by suminkwon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*free_one(char **buffer)
{
	if (buffer && *buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	int	c;

	c = 0;
	if (!s)
		return (0);
	while (s[c] != '\0')
		c++;
	return (c);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (unsigned char)c)
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	char	*res;
	int		i;

	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!res || !s1)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin(char *previous_read, char const *buffer)
{
	char	*res;
	size_t	whole_len;
	size_t	i;
	size_t	j;

	if (!previous_read)
		previous_read = ft_strdup("");
	if (!previous_read)
		return (NULL);
	if (buffer[0] == '\0')
		return (previous_read);
	whole_len = ft_strlen(previous_read) + ft_strlen(buffer);
	res = (char *)malloc(sizeof(char) * (whole_len + 1));
	if (!res)
		return (free_one(&previous_read));
	i = -1;
	while (previous_read[++i])
		res[i] = previous_read[i];
	j = 0;
	while (buffer[j])
		res[i++] = buffer[j++];
	res[whole_len] = '\0';
	previous_read = free_one(&previous_read);
	return (res);
}
