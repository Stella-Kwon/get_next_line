/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suminkwon <suminkwon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 14:03:43 by suminkwon         #+#    #+#             */
/*   Updated: 2024/01/02 21:42:12 by suminkwon        ###   ########.fr       */
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
	if (previous_read && *previous_read)
	{
		free(*previous_read);
		*previous_read = NULL;
	}
	if (buffer && *buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
}

static char *find_newline(char *previous_read, int fd) // read fd and join previous_read + buffer
{
	char *buffer;
	int readsize;

	readsize = 1;
	while (readsize && !ft_strchr(previous_read, '\n'))
	{
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
		{
			// printf("Error in buffer malloc in the find_newline function\n");
			return (NULL);
		}
		readsize = read(fd, buffer, BUFFER_SIZE);
		if (readsize == -1)
		{
			free_both(&previous_read, &buffer);
			// printf("read()function has error which readsize is negative number in find_newline function\n");
			return (NULL);
		}
		// if (!readsize) //해버리면 마지막 줄 프린팅이 안됌 ->NULL이라서 
		// 	free_one(&previous_read);
		// 	break;
		buffer[readsize] = '\0';
		// printf("buffer : %s\n", buffer);
		// buffer malloc을 해줄필요없을때 해주고 싶지않아서 malloc을 while안에 둠
		// 그렇지만 25줄 이상으로 위로 빼줘야 할수도 있음.
		// 사실 readsize가 0이면 join할 필요도 없어서...
		previous_read = ft_strjoin(previous_read, buffer);
		// if (!previous_read)
			// printf("Error in previous_read in the find_newline : ft_strjoin function\n");
		free_one(&buffer);
	}
	// printf("previous_read : %s\n", previous_read);
	return (previous_read);
}

static char *store_line(char *previous_read)
{
	char *line;
	size_t i;

	i = 0;
	// printf("previous_read[i] : %c\n", previous_read[i]);
	if (!previous_read[i])
	{
		// printf("end of the file");
		// free_one(&previous_read); //store_leftover에서 해주기 떄문에 안해주기
		return (NULL);
	}
	while (previous_read[i] != '\n' && previous_read[i] != '\0')
		i++;
	if (previous_read[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
	{
		// printf("Error in mallocing line in store_line function\n");
		free_one(&previous_read);
		return (NULL);
	}
	i = 0;
	while (previous_read[i] != '\n' && previous_read[i])
	{
		line[i] = previous_read[i];
		i++;
	}
	if (previous_read[i] == '\n')
	{
		line[i] = previous_read[i];
		i++;
	}
	line[i] = '\0';
	// printf("line : %s\n", line);
	return (line);
}

static char *store_leftover(char *previous_read)
{
	size_t i;
	size_t j;
	size_t len;
	char *new_previous_read;

	i = 0;
	while (previous_read[i] != '\n' && previous_read[i] != '\0')
		i++;
	if (!previous_read[i])
	{
		// printf("last sentence : no new line\n");
		free_one(&previous_read);
		return (NULL);
	}
	len = (ft_strlen(previous_read) - i);
	new_previous_read = (char *)malloc(sizeof(char) * len);
	if (!new_previous_read)
	{
		// printf("Error malloc in store_leftover\n");
		free_one(&previous_read);
		return (NULL);
	}
	++i;
	j = 0;
	while (previous_read[i])
		new_previous_read[j++] = previous_read[i++];
	new_previous_read[j] = '\0';
	free_one(&previous_read);
	// printf("new previous_read : %s\n", new_previous_read);
	return (new_previous_read);
}

char *get_next_line(int fd)
{
	static char *previous_read;
	char *each_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	previous_read = find_newline(previous_read, fd);
	if (!previous_read)
		return (NULL);
	// printf("s\n");
	each_line = store_line(previous_read);
	// printf("aas\n");
	// 어차피 리턴 eachline이라 안해줘도돼.
	// if (!each_line)
	// 	return (NULL);
	// printf("previous_read after: %s\n", previous_read);
	previous_read = store_leftover(previous_read);
	// if (!previous_read)//여기서 해버리면 마지막 line이 리턴이 안됌.
	//	return (NULL);
	// printf("final line : %s\n", each_line);
	return (each_line);
}
