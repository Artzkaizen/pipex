/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rethink.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuezeri <chuezeri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:54:03 by chuezeri          #+#    #+#             */
/*   Updated: 2025/05/02 16:45:25 by chuezeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void handle_error(int status, const char *message, void (*callback)(void))
{
    if (callback)
        callback();
    if (message)
        perror(message);
    exit(status);
}
int *open_files(int ac, char **argv)
{
    int *fds = malloc(sizeof(int) * 2);
    if (!fds)
        handle_error(EXIT_FAILURE, "Memory allocation failed", NULL);
    fds[0] = open(argv[1], O_RDONLY);
    if (fds[0] == -1)
        handle_error(EXIT_FAILURE, "Failed to open input file", NULL);
    fds[1] = creat(argv[ac - 1], 0644);
    if (fds[1] == -1)
        handle_error(EXIT_FAILURE, "Failed to open output file", NULL);
    return fds;
}

void pipex(t_list **list, t_store *store, t_args *args)
{
    int i = 2;
    while (i < args->max)
    {
        int pipe_fds[2];
        if (pipe(pipe_fds) == -1)
            handle_error(EXIT_FAILURE, "Pipe failed", NULL);

        t_process *proc = fork_and_exec(store->prev_fd, pipe_fds[1], args->argv[i], args->envp);
        if (!proc)
            handle_error(EXIT_FAILURE, "Fork failed", NULL);

        ft_lstadd_back(list, ft_lstnew(proc));

        close(pipe_fds[1]);
        if (store->prev_fd != store->fds[0])
            close(store->prev_fd);
        store->prev_fd = pipe_fds[0];
        i++;
    }
}

int main(int ac, char **argv, char **envp)
{
    if (ac < 5)
        handle_error(EXIT_FAILURE, "Invalid number of arguments", NULL);

    t_store store;
    t_list *list = NULL;
    t_args args = {argv, envp, ac - 2};

    store.fds = open_files(ac, argv);
    store.prev_fd = store.fds[0];

    pipex(&list, &store, &args);

    t_process *last = fork_and_exec(store.prev_fd, store.fds[1], argv[ac - 2], envp);
    if (!last)
        handle_error(EXIT_FAILURE, "Fork failed for last command", NULL);
    ft_lstadd_back(&list, ft_lstnew(last));

    if (store.prev_fd != store.fds[0])
        close(store.prev_fd);
    close(store.fds[0]);
    close(store.fds[1]);
    free(store.fds);

    wait_for_processes(&list);
    return 0;
}
