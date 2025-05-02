/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuezeri <chuezeri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:20:04 by chuezeri          #+#    #+#             */
/*   Updated: 2025/04/30 11:54:54 by chuezeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int is_separator(char c, const char *seps)
{
    while (*seps)
    {
        if (c == *seps)
            return (1);
        seps++;
    }
    return (0);
}

static int count_words(char *str, const char *seps)
{
    int count = 0;
    int in_word = 0;

    while (*str)
    {
        if (!is_separator(*str, seps) && !in_word)
        {
            in_word = 1;
            count++;
        }
        else if (is_separator(*str, seps))
            in_word = 0;
        str++;
    }
    return (count);
}

static char *extract_word(char *str, const char *seps)
{
    int len = 0;
    while (str[len] && !is_separator(str[len], seps))
        len++;

    char *word = (char *)malloc(sizeof(char) * (len + 1));
    if (!word)
        return (NULL);

    for (int i = 0; i < len; i++)
        word[i] = str[i];
    word[len] = '\0';
    return word;
}

static void *ft_freeall(char **strs, int i)
{
    while (i >= 0)
        free(strs[i--]);
    free(strs);
    return (NULL);
}

char **ft_split(char *str, char *seps)
{
    int i = 0;
    int words = count_words(str, seps);

    if (!str)
        return (NULL);
    char **result = (char **)malloc(sizeof(char *) * (words + 1));
    if (!result)
        return (NULL);

    while (*str)
    {
        if (!is_separator(*str, seps))
        {
            result[i] = extract_word(str, seps);
            if (!result[i])
                return (ft_freeall(result, i - 1));
            i++;
            while (*str && !is_separator(*str, seps))
                str++;
        }
        else
            str++;
    }
    result[i] = NULL;
    return result;
}
