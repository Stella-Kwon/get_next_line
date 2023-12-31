/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suminkwon <suminkwon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 14:03:40 by suminkwon         #+#    #+#             */
/*   Updated: 2023/12/28 13:15:27 by suminkwon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

unsigned int ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			return (i);
		i++;
	}
	if (s[i] == (unsigned char)c)
		return (i);
	return (0);
}

// char *ft_strdup(const char *s1)
// {
// 	char *res;
// 	int i;

// 	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
// 	if (!res || !s1)
// 		return (NULL);
// 	i = 0;
// 	while (s1[i] != '\0')
// 	{
// 		res[i] = s1[i];
// 		i++;
// 	}
// 	res[i] = '\0';
// 	return (res);
// }

char *ft_substr(char const *s, unsigned int start, size_t len)
{
	char *res;
	unsigned int min;
	unsigned int slen;
	unsigned int i;

	//이미 위에서 protect다 해서
	// if (!s)
	// 	return (NULL);
	slen = ft_strlen(s);
	// if (slen <= start || len == 0)
	// 	return (ft_strdup(""));
	if (len < slen - start)
		min = len;
	else
		min = slen - start;
	res = (char *)malloc(min + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < min)
		res[i++] = s[start++];
	res[i] = '\0';
	free((char *)s);
	s = NULL;
	return (res);
}

// size_t	ft_strlen_without_newline(const char *s)
// {
// 	size_t	c;
// 	size_t	i;

// 	c = 0;
// 	i = 0;
// 	while (s[c] != '\0')
// 	{
// 		if (s[c] == '\n')
// 			c++;
// 		c++;
// 		i++;
// 	}
// 	return (i);
// }
size_t ft_strlen(const char *s)
{
	int c;

	c = 0;
	if (!s)
		return (0);
	while (s[c] != '\0')
		c++;
	return (c);
}

size_t ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t srclen;
	size_t i;

	srclen = ft_strlen(src);
	i = 0;
	if (dstsize == 0)
		return (srclen);
	while (i < (dstsize - 1) && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srclen);
}

char *ft_strjoin(char *previous_read, char const *buffer)
{
	char *res;
	size_t whole_len;
	size_t	i;
	size_t	j;

	if (!previous_read)
	{
		previous_read = (char *)malloc(1);
		if (!previous_read)
		{
			printf("Error in previous_read malloc in the join_str function\n");
			return (NULL);
		}
		previous_read[0] = '\0';
	}
	whole_len = ft_strlen(previous_read) + ft_strlen(buffer);
	//already protected
	// if (!previous_read && !buffer)
	// 	return (NULL);
	// if (previous_read && !buffer)
	// 	return ((char *)previous_read);
	// if (!previous_read && buffer)
	// 	return ((char *)buffer);
	res = (char *)malloc(sizeof(char) * (whole_len + 1));
	if (!res)
		return (NULL);
	// malloc 함수는 새로운 메모리 블록을 할당하고 해당 메모리의 시작 주소를 반환합니다.
	// res에는 이 새로운 메모리 블록의 시작 주소가 저장되기 때문에 ft_strlcpy와 ft_strlcat에서 deferencing ** 이 아닌
	// 그대로의 char *로 받아도 이 메모리 블록에 대한 작업을 수행하면 res가 가리키는 메모리에 변화가 생깁니다.
	// 그 주소를 복사해 보내는게 아니라 블록시작의 주소가 저장되기 때문이다.
	// 기본적으로 char *는 그 포인터의 주소를 가지고있고, 그 값으로 그 포인터가 가르키는 데이터의 첫 메모리의 주소가 들어가 있기에  **dereferencing으로 &주소를 넣어 그것의 안으로 또 들어가는 작업을 해야 원하는 주소의 값에 도달하게된다.
	i = -1;
	while (previous_read[++i])
		res[i] = previous_read[i]; 
	j = -1;
	while (buffer[++j])
		res[i++] = buffer[j];
	res[whole_len] = '\0';
	free(previous_read);
	previous_read = NULL;
   	// printf("res in strjoin function : %s\n", res);
	return (res);
}
