/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuezeri <chuezeri@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 11:51:44 by chuezeri          #+#    #+#             */
/*   Updated: 2025/06/02 16:40:45 by chuezeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	handle_error(int status, const char *message, void (*callback)(void))
{
	if (callback)
		callback();
	if (message)
		perror(message);
	exit(status);
}

void	free_args(void ***str)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			free(str[i][j]);
			j++;
		}
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_paths(void **array)
{
	size_t	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	wait_free_exit(char ***cmds, int status)
{
	int	temp;

	temp = errno;
	while (wait(NULL) != -1)
		;
	errno = temp;
	if (cmds)
		free_args((void ***)cmds);
	exit(status);
}
