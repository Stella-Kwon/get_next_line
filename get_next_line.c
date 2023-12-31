/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suminkwon <suminkwon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 14:03:43 by suminkwon         #+#    #+#             */
/*   Updated: 2023/12/31 08:36:13 by suminkwon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> //지 워 야 해!

static void free_one(char **buffer)
{
	if (buffer && *buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
}

static void free_both(char **previous_read, char **buffer)
{
	if (previous_read && *previous_read && buffer && *buffer)
	{
		free(*previous_read);
		free(*buffer);
		*previous_read = NULL;
		*buffer = NULL;
	}
}

static char *join_str(char *previous_read, char *buffer) // \n나올때까지 버퍼 모자르면 저장하기.
{
	// int buffer_size;
	char *res;

	// if (!previous_read)
	// {
	// 	printf("Error in previous_read malloc in the join_str function\n");
	// 	return (NULL);
	// }

	// if (!*buffer) // end of line.
	// {
	// 	printf("END OF THE LINE : buffer NULL : join_str function\n");
	// 	return (NULL);
	// }
	// buffer_size = ft_strlen(previous_read) + BUFFER_SIZE;
	// ft_strlcat(previous_read, buffer, buffer_size + 1);
	// printf("previous_read : %s\nbuffer : %s\n", previous_read, buffer);
	res = ft_strjoin(previous_read, buffer);
	// printf("\nafter\n\n");
	// printf("buffer: %s\n", buffer);
	// size_t i = ft_strlen(buffer);
	// printf("buffersize : %zu\n, buffer_size : %d\n", i, buffer_size);
	// printf("res : %s\n",res);
	if (!res)
	{
		free_both(&previous_read, &buffer);
		return (NULL);
	}
	// free_one(&previous_read);
	previous_read = res;
	// printf("previous_read : %s\n", previous_read);
	// if (!previous_read)
	// {
	// 	printf("Error in malloc ft_strjoin in str_join function\n");
	// 	return (NULL);
	// }
	// printf("previous_read : %s\nbuffer : %s\n", previous_read, buffer);
	return (previous_read);
}

static char *find_newline(char **previous_read, int fd)
{
	char *buffer;
	int readsize;

	readsize = 1;
	while (readsize && !ft_strchr(*previous_read, '\n'))
	{
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
		{
			printf("Error in buffer malloc in the find_newline function\n");
			return (NULL);
		}
		// printf("\nread\n\n");
		readsize = read(fd, buffer, BUFFER_SIZE); // 버퍼안에 읽은게 들어가겠지
		// printf("readsize : %d\n", readsize);
		if (readsize == -1) //|| readsize == 0)
		{
			free_one(&buffer);
			printf("read()function has error which readsize is negative number in find_newline function\n");
			return (NULL);
		}
		// if (readsize == 0)// nl 만 있는걸 못읽어
		// {
		// 	printf("END OF THE LINE : buffer NULL : find_newline function\n");
		// 	free_one(&buffer);
		// 	return (NULL);
		// }
		buffer[readsize] = '\0';
		// printf("buffer : %s\n", buffer);
		*previous_read = join_str(*previous_read, buffer);
		// printf("annnna\n");
		free_one(&buffer);
	}
	return (*previous_read);
}

static char *store_line(char **previous_read)
{
	char			*result;
	char			*new_previous_read;
	unsigned int	start;
	size_t 			len;

	start = ft_strchr(*previous_read, '\n') + 1;
	len = ft_strlen(*previous_read) - (start);
	result = (char *)malloc(start + 1);
	if (!result)
	{
		printf("ERROR in result malloc in the store_line function\n");
		return (NULL);
	}
	ft_strlcpy(result, *previous_read, start + 1);
	new_previous_read = ft_substr(*previous_read, start, len);
	if (!new_previous_read)
	{
		printf("Error in mallocing new_previous_read in store_line function\n");
		return (NULL);
	}
	*previous_read = new_previous_read;
	// printf("result in storline : %s\n", result);
	// printf("previous_read in storline : %s\n", *previous_read);
	// if (!result[previous_read_size])
	// 	result[previous_read_size] = '\n';
	return (result);
}

char *get_next_line(int fd)
{
	static char *previous_read;
	char *each_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (previous_read)
			free_one(&previous_read);
		return (NULL);
	}
	//먼저 맬록해주면 free해줘야해
	// if (!previous_read)
	// {
	// 	previous_read = (char *)malloc(1);
	// 	if (!previous_read)
	// 	{
	// 		printf("Error in previous_read malloc in the join_str function\n");
	// 		return (NULL);
	// 	}
	// 	previous_read[0] = '\0';
	// }
	// printf("previous_read : %s\n", previous_read);
	previous_read = find_newline(&previous_read, fd);
	
	if (!previous_read) //한번에 관리해야지. 어떨때는 free해줘야하고 어떨땐 안해주게됌.
		
		return (NULL);
	each_line = store_line(&previous_read);
	if (!each_line)
		return (NULL);
	// printf("previous_read after: %s\n", previous_read);
	return (each_line);
}
