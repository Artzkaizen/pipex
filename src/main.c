/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuezeri <chuezeri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:54:03 by chuezeri          #+#    #+#             */
/*   Updated: 2025/05/02 16:46:33 by chuezeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int open_file(const char *path, int create)
{
    if (create)
        return creat(path, 0644);
    return open(path, O_RDONLY);
}

void handle_error(int status, const char *message, void (*callback)(void))
{
    if (callback)
        callback();
    if (message)
        perror(message);
    exit(status);
}

void execute_command(char *cmd_str, char **envp)
{
    char **args = ft_split(cmd_str, " ");
    char *path = find_command_path(args[0], envp);
    if (!path)
        handle_error(EXIT_FAILURE, "Command not found", NULL);
    execve(path, args, envp);
    perror("execve failed");
    exit(EXIT_FAILURE);
    (void)cmd_str;
    (void)envp;
}

int main(int ac, char **argv, char **envp)
{
    int in_fd;
    int out_fd;
    int pipe_fd[2];
    pid_t pid1;
    pid_t pid2;
    // char buffer[100];
    int status_in;
    int status_out;

    t_list *list = NULL;

    list = ft_lstnew(list);
    if (!list)
        handle_error(EXIT_FAILURE, "Memory allocation failed", NULL);

    if (ac != 5)
        handle_error(EXIT_FAILURE, "Invalid number of arguments", NULL);
    in_fd = open_file(argv[1], 0);

    if (in_fd == -1)
        handle_error(EXIT_FAILURE, "Failed to open input file", NULL);
    out_fd = open_file(argv[4], 1);
    if (out_fd == -1)
        handle_error(EXIT_FAILURE, "Failed to open output file", NULL);
    if (pipe(pipe_fd) == -1)
    {
        close(in_fd);
        close(out_fd);
        // handle_error(EXIT_FAILURE, "Pipe creation failed", close_files);
        return (perror("Pipe creation failed"), EXIT_FAILURE);
    }

    pid1 = fork();
    if (pid1 == -1)
    {
        perror("Fork 1 failed");
        close(in_fd);
        close(out_fd);
        return (EXIT_FAILURE);
    }
    if (pid1 == 0)
    {                      // --- Child 1 (runs cmd1) ---
        close(pipe_fd[0]); // Child 1 doesn't need to read from the pipe

        // Redirect stdin to input file
        dup2(in_fd, STDIN_FILENO);
        close(in_fd); // Safe to close original after dup

        // Redirect stdout to pipe write end
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);

        close(out_fd); // Child 1 doesn't use outfile

        // Execute cmd1 (e.g., "grep something")
        execute_command(argv[2], envp);

        // If execve fails:
        perror("Execve cmd1 failed");
        exit(EXIT_FAILURE);
    }
    pid2 = fork();
    if (pid2 == -1)
    {
        perror("Fork 2 failed");
        close(in_fd);
        close(out_fd);
        return (EXIT_FAILURE);
    }

    if (pid2 == 0)
    {                      // --- Child 2 (runs cmd2) ---
        close(pipe_fd[1]); // Child 2 doesn't need to write to the pipe

        // Redirect stdin to pipe read end
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]); // Close original after dup

        // Redirect stdout to outfile_fd
        dup2(out_fd, STDOUT_FILENO);
        close(out_fd); // Close original after dup

        close(in_fd); // Child 2 doesn't use infile

        // Prepare arguments and execute cmd2
        execute_command(argv[3], envp);
        perror("Execve cmd2 failed");
        exit(EXIT_FAILURE);
    }

    // read_and_clean(buffer, fd, STDIN_FILENO);
    // ft_putstr_fd("\nworks\n", STDOUT_FILENO);
    // read_and_clean(buffer, STDIN_FILENO, STDOUT_FILENO);

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    close(in_fd);
    close(out_fd); // Close the output file descriptor

    // 6. Wait for both children to finish
    waitpid(pid1, &status_in, 0);
    waitpid(pid2, &status_out, 0);

    // close(fd);
    return (EXIT_SUCCESS);
}