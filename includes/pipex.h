/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuezeri <chuezeri@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:57:14 by chuezeri          #+#    #+#             */
/*   Updated: 2025/05/06 19:31:57 by chuezeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "utils.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>

typedef struct s_process
{
	int				fd;
	pid_t			pid;
	int				status;
}					t_process;

typedef struct s_list
{
	t_process		*content;
	struct s_list	*next;
}					t_list;

typedef struct s_store
{
	int				*fds;
	int				prev_fd;
	int				pipe_fds[2];

}					t_store;

typedef struct s_args
{
	char			**argv;
	char			**envp;
	int				max;
}					t_args;

void				ft_lstclear(t_list **lst);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_back(t_list **lst, t_list *new);

void				wait_for_processes(t_list **list);
t_process			*fork_and_exec(int in_fd, int out_fd, char *cmd,
						char **envp);

char				*find_command_path(char *cmd, char **envp);

void				handle_error(int status, const char *message,
						void (*callback)(void));
char				*find_command_path(char *cmd, char **envp);

#endif // PIPEX_H
