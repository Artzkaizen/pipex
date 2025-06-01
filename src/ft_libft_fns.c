/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft_fns.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuezeri  <chuezeri@student.42.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 12:34:39 by chuezeri          #+#    #+#             */
/*   Updated: 2025/06/01 12:39:42 by chuezeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_strcat(char *dest, const char *src)
{
	size_t	count;
	size_t	lenght;

	count = 0;
	lenght = ft_strlen(dest);
	while (src[count])
	{
		dest[lenght + count] = src[count];
		count++;
	}
	dest[lenght + count] = '\0';
	return (dest);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	len;
	char	*dest;

	len = ft_strlen(s1) + ft_strlen(s2);
	dest = (char *)malloc(sizeof(char) * len + 1);
	if (!dest)
		return (dest);
	dest[0] = '\0';
	ft_strcat(dest, s1);
	ft_strcat(dest, s2);
	return (dest);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t		i;
	size_t		j;
	size_t		len;

	i = 0;
	len = ft_strlen((char *)needle);
	if (haystack == needle || !len)
		return ((char *)haystack);
	while (haystack[i] && i < n)
	{
		j = 0;
		while ((n - i >= len) && haystack[j + i] && needle[j] && haystack[i
				+ j] == needle[j])
			j++;
		if (needle[j] == '\0')
			return ((char *)&haystack[i]);
		i++;
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (*s1 && *s2 && n > 0)
	{
		if (*s1 != *s2)
			return ((unsigned char) *s1 - (unsigned char) *s2);
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char) *s1 - (unsigned char) *s2);
}

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	count;
	size_t	length;
	size_t	dest_length;
	size_t	src_length;

	count = 0;
	length = ft_strlen(dest);
	dest_length = length;
	src_length = ft_strlen(src);
	if (size <= dest_length)
		return (size + src_length);
	while (src[count] && count < size - dest_length - 1)
	{
		dest[length + count] = src[count];
		src[count] = 0;
		count++;
	}
	dest[length + count] = '\0';
	return (length + count);
}
