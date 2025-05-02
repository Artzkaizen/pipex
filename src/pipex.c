/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuezeri <chuezeri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:55:23 by chuezeri          #+#    #+#             */
/*   Updated: 2025/04/30 11:31:50 by chuezeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void wait_for_processes(t_list **list)
{
    t_list *tmp = *list;
    while (tmp)
    {
        waitpid(tmp->content->pid, &tmp->content->status, 0);
        tmp = tmp->next;
    }
}

void execute_command(char *cmd_str, char **envp)
{
    char **args = ft_split(cmd_str, " ");
    char *path = find_command_path(args[0], envp);
    if (!path)
    { /* error */
        handle_error(EXIT_FAILURE, "Command not found", NULL);
    }
    execve(path, args, envp);
    // // If execve returns, it's an error
    perror("execve failed");
    // // Free allocated memory for path and args
    exit(EXIT_FAILURE);
    (void)cmd_str;
    (void)envp;
}

t_process *fork_and_exec(int in_fd, int out_fd, char *cmd, char **envp)
{
    t_process *process = malloc(sizeof(t_process));
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

    return process;
}
