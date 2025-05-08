/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rethink.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuezeri <chuezeri@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:54:03 by chuezeri          #+#    #+#             */
/*   Updated: 2025/05/08 19:12:39 by chuezeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_error(int status, const char *message, void (*callback)(void))
{
	if (callback)
		callback();
	if (message)
		perror(message);
	exit(status + 126);
}

int	*open_files(int ac, char **argv)
{
	int	*fds;

	fds = malloc(sizeof(int) * 2);
	if (!fds)
		handle_error(EXIT_FAILURE, "Memory allocation failed", NULL);
	fds[0] = open(argv[1], O_RDONLY);
	// if (fds[0] == -1)
	// 	handle_error(EXIT_FAILURE, "Failed to open input file", NULL);
	fds[1] = creat(argv[ac - 1], 0644);
	// if (fds[1] == -1)
	// 	handle_error(EXIT_FAILURE, "Failed to open output file", NULL);
	return (fds);
}

int	pipex(t_list **list, t_store *store, const t_args *args)
{
	int			i;
	int			pipe_fds[2];
	t_process	*proc;

	i = 2;
	while (i < args->max)
	{
		if (pipe(pipe_fds) == -1)
			handle_error(EXIT_FAILURE, "Pipe failed", NULL);
		if (pipe_fds[0] == -1 || pipe_fds[1] == -1)
		{
			close(pipe_fds[0]);
			close(pipe_fds[1]);
			continue ;
		}
		proc = fork_and_exec(store->prev_fd, pipe_fds[1], args->argv[i],
				args->envp);
		if (!proc)
			return (EXIT_FAILURE);
		ft_lstadd_back(list, ft_lstnew(proc));
		close(pipe_fds[1]);
		if (store->prev_fd != store->fds[0])
			close(store->prev_fd);
		store->prev_fd = pipe_fds[0];
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int ac, char **argv, char **envp)
{
	t_store			store;
	t_list			*list;
	const t_args	args = {argv, envp, ac - 2};
	t_process		*last;
	int				pipex_status;

	if (ac < 5)
		handle_error(EXIT_FAILURE, "Invalid number of arguments", NULL);
	list = NULL;
	store.fds = open_files(ac, argv);
	store.prev_fd = store.fds[0];
	pipex_status = pipex(&list, &store, &args);
	if (pipex_status == EXIT_FAILURE)
	{
		free(store.fds);
		return (EXIT_FAILURE);
	}
	last = fork_and_exec(store.prev_fd, store.fds[1], argv[ac - 2], envp);
	if (!last)
		(free(store.fds), handle_error(EXIT_FAILURE,
				"Fork failed for last command", NULL));
	ft_lstadd_back(&list, ft_lstnew(last));
	if (store.prev_fd != store.fds[0])
		close(store.prev_fd);
	wait_for_processes(&list);
	close(store.fds[0]);
	close(store.fds[1]);
	ft_lstclear(&list);
	free(store.fds);
	return (0);
}
