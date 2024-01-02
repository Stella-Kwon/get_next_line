/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suminkwon <suminkwon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 14:03:40 by suminkwon         #+#    #+#             */
/*   Updated: 2024/01/02 21:47:55 by suminkwon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char			*res;
// 	unsigned int	min;
// 	unsigned int	slen;
// 	unsigned int	i;

// 	slen = ft_strlen(s);
// 	if (slen <= start || len == 0)
// 		return (ft_strdup(""));
// 	if (len < slen - start)
// 		min = len;
// 	else
// 		min = slen - start;
// 	res = (char *)malloc(min + 1);
// 	if (!res)
// 		return (NULL);
// 	i = 0;
// 	while (i < min)
// 		res[i++] = s[start++];
// 	res[i] = '\0';
// 	return (res);
// }

char	*ft_strjoin(char *previous_read, char const *buffer)
{
	char	*res;
	size_t	whole_len;
	size_t	i;
	size_t	j;

	if (!previous_read)
		previous_read = ft_strdup("");
	if (!previous_read)// 이미 buffer 가 없을 일은 없어
	{
		// printf("Error in previous_read malloc or NULL in buffer in the join_str function\n");
		return (NULL);
	}
	whole_len = ft_strlen(previous_read) + ft_strlen(buffer);
	res = (char *)malloc(sizeof(char) * (whole_len + 1));
	if (!res)
		return (NULL);
	i = -1;
	while (previous_read[++i])
		res[i] = previous_read[i];
	j = 0;
	while (buffer[j])
		res[i++] = buffer[j++];
	res[whole_len] = '\0';
	free(previous_read);
	previous_read = NULL;
	return (res);
}
