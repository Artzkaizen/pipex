/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuezeri <chuezeri@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 11:44:50 by chuezeri          #+#    #+#             */
/*   Updated: 2025/06/02 16:40:42 by chuezeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	***parse_args(size_t size, char *argv[])
{
	char	***cmds;
	size_t	i;

	cmds = malloc((size + 1) * sizeof(char **));
	if (!cmds)
		handle_error(EXIT_FAILURE, "parsing", NULL);
	i = 0;
	while (i < size)
	{
		cmds[i] = ft_split(argv[i], ' ');
		if (!cmds[i] || !cmds[i][0])
		{
			cmds[i + 1] = NULL;
			free_args((void ***)cmds);
			handle_error(EXIT_FAILURE, "parsing", NULL);
		}
		i++;
	}
	cmds[size] = NULL;
	return (cmds);
}

int	main(int argc, char *argv[], char **env)
{
	t_pipex	info;
	int		num_cmds;
	int		stat_loc;
	pid_t	pid;

	num_cmds = argc - 3;
	info.here_doc = (argc > 1 && ft_strncmp(argv[1], "here_doc", 9) == 0);
	if (info.here_doc)
	{
		info.hd_limiter = argv[2];
		num_cmds--;
	}
	if (num_cmds < 2)
		exit(EXIT_FAILURE);
	info.infile = argv[1];
	info.outfile = argv[argc - 1];
	info.cmds = parse_args(num_cmds, &argv[2 + info.here_doc]);
	set_cmd_path(info.cmds, env);
	pid = pipex(&info, num_cmds + info.here_doc, env);
	waitpid(pid, &stat_loc, 0);
	wait_free_exit(info.cmds, WEXITSTATUS(stat_loc));
}
