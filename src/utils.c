/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuezeri <chuezeri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:59:30 by chuezeri          #+#    #+#             */
/*   Updated: 2025/04/30 12:50:42 by chuezeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "utlis.h"

void ft_putstr_fd(char *str, int fd)
{
    int i;

    i = 0;
    while (str[i])
    {
        write(fd, &str[i], 1);
        i++;
    }
}

size_t ft_strlen(const char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

char *ft_strchr(const char *s, int c)
{
    char *str;

    str = (char *)s;
    while (*str || *str == (unsigned char)c)
    {
        if (*str == (unsigned char)c)
            return (str);
        str++;
    }
    return (NULL);
}

char *ft_strdup(const char *s)
{
    int lenght;
    char *dest;

    lenght = 0;
    while (s[lenght])
        lenght++;
    dest = (char *)malloc(sizeof(char) * (lenght + 1));
    if (!dest)
        return (NULL);
    while (lenght >= 0)
    {
        dest[lenght] = s[lenght];
        lenght--;
    }
    return (dest);
}

char *ft_strtok(char *str, const char *sep)
{
    static char *save;
    char *start;
    int i;

    if (str)
        save = str;
    if (!save || !*save)
        return (NULL);
    while (*save)
    {
        i = 0;
        while (sep[i] && *save != sep[i])
            i++;
        if (!sep[i])
            break;
        save++;
    }
    if (!*save)
        return (NULL);
    start = save;
    while (*save)
    {
        i = 0;
        while (sep[i] && *save != sep[i])
            i++;
        if (sep[i])
        {
            *save = '\0';
            save++;
            break;
        }
        save++;
    }
    return (start);
}
