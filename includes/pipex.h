/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuezeri <chuezeri@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 11:43:34 by chuezeri          #+#    #+#             */
/*   Updated: 2025/06/02 16:42:07 by chuezeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define PIPEX_ERROR -1

typedef struct s_pipex
{
	char	***cmds;
	int		pipe[2];
	int		here_doc;
	char	*hd_limiter;
	char	*infile;
	char	*outfile;
}			t_pipex;

void		free_args(void ***str);

void		free_paths(void **array);
void		set_cmd_path(char ***cmds, char **env);
void		wait_free_exit(char ***cmds, int status);
int			redirect_io(int input_fd, int output_fd);
pid_t		pipex(t_pipex *info, size_t num_childs, char **env);
void		handle_error(int status, const char *message,
				void (*callback)(void));

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif // BUFFER SIZE

typedef struct s_file
{
	int		fd;
	size_t	line_len;
	int		bytes_read;
	int		bytes_parsed;
	char	*line;
}			t_file;

char		*get_next_line(int fd);

// LIBFT FUNCTIONS

size_t		ft_strlen(const char *str);
char		**ft_split(char *str, char sep);
void		*ft_calloc(size_t nmemb, size_t size);
size_t		ft_strlcat(char *dest, char *src, size_t size);
char		*ft_strjoin(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t n);

#endif