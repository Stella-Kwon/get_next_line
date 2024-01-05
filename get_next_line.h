/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suminkwon <suminkwon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 14:04:18 by suminkwon         #+#    #+#             */
/*   Updated: 2024/01/05 02:07:51 by suminkwon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1
#endif

#include <unistd.h>
#include <stdlib.h>

char *get_next_line(int fd);
size_t ft_strlen(const char *s);
char *ft_strdup(const char *s1);
size_t ft_strlcpy(char *dst, const char *src, size_t dstsize);
char *ft_strjoin(char *previous_read, char const *buffer);
char *ft_strchr(const char *s, int c);
void *free_one(char **buffer);
#endif