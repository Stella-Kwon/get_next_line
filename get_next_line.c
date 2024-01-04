/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suminkwon <suminkwon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 14:03:43 by suminkwon         #+#    #+#             */
/*   Updated: 2024/01/04 22:20:33 by suminkwon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> //지 워 야 해!

static void *free_both(char **previous_read, char **buffer)
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
	return (NULL);
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
				return (free_one(&previous_read));
			}
			readsize = read(fd, buffer, BUFFER_SIZE);
			if (readsize == -1)
			{
				// free_one(&buffer); // previous free at getnextline function // but didnot work it out
				// printf("read()function has error which readsize is negative number in find_newline function\n");
				// return (NULL);
				return (free_both(&previous_read, &buffer));
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
			buffer = free_one(&buffer);
		}
		// printf("previous_read : %s\n", previous_read);
		return (previous_read);
}

static int store_line(char *previous_read, char **line) // only if it has the\n
{
	size_t i;

	i = 0;
	// printf("previous_read[i] : %c\n", previous_read[i]);
	if (!previous_read[i])
	{
		// printf("end of the file");
		// previous_read = free_one(&previous_read); //store_leftover에서 해주기 떄문에 안해주기
		return (-1);
	}
	// while (previous_read[i] != '\n' && previous_read[i] != '\0')
	while (previous_read[i] && previous_read[i] != '\n')
		i++;
	if (previous_read[i] == '\n')
		i++;
	// printf("i = %zu\n", i); //through this you can find out that when it gets in the (!*line)
	*line = (char *)malloc(sizeof(char) * (i + 1));
	if (!*line)
	{
		// printf("Error in mallocing line in store_line function\n");
		// previous_read = free_one(&previous_read); // 밑에서 previous가 NULL이 되면 안되는 상황.
		return (-1);
	}
	i = 0;
	// while (previous_read[i] != '\n' && previous_read[i])
	while (previous_read[i] && previous_read[i] != '\n')
	{
		(*line)[i] = previous_read[i];
		i++;
	}
	if (previous_read[i] == '\n')
	{
		(*line)[i] = previous_read[i];
		i++;
	}
	(*line)[i] = '\0';
	// printf("line : %s\n", line);
	return (0);
}

static char *store_leftover(char *previous_read)//, char **each_line)
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
		return (free_one(&previous_read));
	}
	len = (ft_strlen(previous_read) - i + 1);
	new_previous_read = (char *)malloc(sizeof(char) * len + 1);
	if (!new_previous_read)
	{
		// printf("Error malloc in store_leftover\n");
		// if (*each_line)
		// 	free_both(&previous_read, each_line); //each_line will eventually get freed in main even it is not malloced properly or in whatever stance
		// else
		// 	free_one(&previous_read);
		// return (NULL);
		return (free_one(&previous_read));
	}
	++i;
	j = 0;
	while (previous_read[i])
		new_previous_read[j++] = previous_read[i++];
	new_previous_read[j] = '\0';
	previous_read = free_one(&previous_read);
	// printf("new previous_read : %s\n", new_previous_read);
	return (new_previous_read);
}

char *get_next_line(int fd)
{
	static char *previous_read;
	char *line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	previous_read = find_newline(previous_read, fd);
	if (!previous_read) // i will just free from here
		// free_one(&previous_read);
		return (NULL);
	// printf("s\n");
	if (store_line(previous_read, &line) < 0)
		return (free_one(&previous_read));
	// printf("aas\n");
	// 어차피 리턴 eachline이라 안해줘도돼.
	// if (!line)
	// 	return (NULL);
	// printf("previous_read after: %s\n", previous_read);
	// if (!line && !previous_read)
	// 	return (NULL);
	previous_read = store_leftover(previous_read);//, &line);
	// if (!previous_read)//여기서 해버리면 마지막 line이 리턴이 안됌.
	//	return (NULL);
	// printf("final line : %s\n", line);
		return (line);
}
