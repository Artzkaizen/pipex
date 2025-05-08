/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuezeri <chuezeri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:55:23 by chuezeri          #+#    #+#             */
/*   Updated: 2025/05/08 15:55:00 by chuezeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void wait_for_processes(t_list **list)
{
	t_list *tmp;

	tmp = *list;
	while (tmp)
	{
		waitpid(tmp->content->pid, &tmp->content->status, WNOHANG);
		tmp = tmp->next;
	}
}

void execute_command(char *cmd_str, char **envp)
{
	char **args;
	char *path;

	args = ft_split(cmd_str, ' ');
	path = find_command_path(args[0], envp);
	if (!path)
		handle_error(EXIT_FAILURE, "Command not found", NULL);
	execve(path, args, envp);
	perror("execve failed");
	exit(EXIT_FAILURE);
	(void)cmd_str;
	(void)envp;
}

t_process *fork_and_exec(int in_fd, int out_fd, char *cmd, char **envp)
{
	t_process *process;

	process = malloc(sizeof(t_process));
	if (!process)
		return (perror("malloc"), NULL);
	process->pid = fork();
	if (process->pid == -1)
		return (perror("fork"), NULL);
	if (process->pid == 0)
	{
		if (in_fd != STDIN_FILENO)
		{
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		if (out_fd != STDOUT_FILENO)
		{
			dup2(out_fd, STDOUT_FILENO);
			close(out_fd);
		}
		execute_command(cmd, envp);
		exit(EXIT_FAILURE);
	}
	return (process);
}
