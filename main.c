/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suminkwon <suminkwon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 11:13:36 by suminkwon         #+#    #+#             */
/*   Updated: 2024/01/02 17:57:18 by suminkwon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h> // open 이랑 O_RDONLY and O_CREAT

int main(void)
{
    int fd;
    char *result;
    int i;
    // char buffer[42];
    ssize_t bytesread;

    fd = open("test1.txt", O_RDONLY | O_CREAT, 0644);
    if (fd < 0)
    {
        printf("Error in opening\n");
        return 0;
    }
    i = 1;
    bytesread = 1; // 맨뒤로가기때문에 다시 닫고 오픈해줘야해

    // printf("byteread:%zu\n", bytesread);

    // close(fd);//닫으면 fd가 새롭게 열리기때문에 그냥 다시 open해도 처음으로 읽히기때문에

    fd = open("test1.txt", O_RDONLY | O_CREAT, 0644);
    if (fd < 0)
    {
        printf("Error in second opening\n");
        return 0;
    }

    while (bytesread)
    {
        result = get_next_line(fd);
        if (!result)
        {
            printf("no line in fd :: main.c\n");
            result = NULL;
            return (0);
        }
        printf("%d line : %s\n", i, result);
        free(result);
        result = NULL;
        // bytesread = read(fd, buffer, sizeof(buffer));
        // bytesread = read(fd, buffer, sizeof(buffer));
        // printf("bytesread: %zd\n", bytesread);
        i++;
    }
    
    close(fd);
    // fscanf(stdin, "c");
    // system("leaks get_next_line");
    return 0;
}