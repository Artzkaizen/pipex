/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuezeri <chuezeri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:01:08 by chuezeri          #+#    #+#             */
/*   Updated: 2025/04/30 11:55:13 by chuezeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

#include <unistd.h>

size_t ft_strlen(const char *str);
char *ft_strdup(const char *s);
char *ft_strchr(const char *s, int c);
void ft_putstr_fd(char *str, int fd);
char **ft_split(char *str, char *sep);
char *ft_strtok(char *str, const char *sep);

#endif // UTILS