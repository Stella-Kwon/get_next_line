/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suminkwon <suminkwon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 11:13:36 by suminkwon         #+#    #+#             */
/*   Updated: 2024/01/05 01:37:34 by suminkwon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h> // open 이랑 O_RDONLY and O_CREAT

int main(void)
{
    int fd1;  
    int fd2;
    int fd3;
    char *result1;
    char *result2;
    char *result3;
    int i;
    
    fd1 = open("test1.txt", O_RDONLY | O_CREAT, 0644);
    if (fd1 < 0)
    {
        printf("Error in opening fd1\n");
        return 0;
    }
    
    fd2 = open("test2.txt", O_RDONLY | O_CREAT, 0644);
    if (fd2 < 0)
    {
        printf("Error in opening fd2\n");
        return 0;
    }
    
    fd3 = open("test3.txt", O_RDONLY | O_CREAT, 0644);
    if (fd3 < 0)
    {
        printf("Error in opening fd3\n");
        return 0;
    }
    
    i = 1;
    while (1)
    {
        result1 = get_next_line(fd1);
        if (!result1)
        {
            printf("no line in fd1 :: main.c\n");
            result1 = NULL;
            return (0);
        }
        printf("result1 : %d line : %s\n", i, result1);

        result2 = get_next_line(fd2);
        if (!result2)
        {
            printf("no line in fd2 :: main.c\n");
            result2 = NULL;
            return (0);
        }
        printf("result2 : %d line : %s\n", i, result2);
        
        result3 = get_next_line(fd3);
        if (!result3)
        {
            printf("no line in fd3 :: main.c\n");
            result3 = NULL;
            return (0);
        }
        
        printf("result3 : %d line : %s\n", i, result3);
        free(result1);
        result1 = NULL;
        free(result2);
        result2 = NULL;
        free(result3);
        result3 = NULL;
        i++;
        printf("i : %d\n", i);
    }
    close(fd1);
    close(fd2);
    close(fd3);
    
    return (0);
}