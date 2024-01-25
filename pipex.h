/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 08:47:22 by jberay            #+#    #+#             */
/*   Updated: 2024/01/25 08:28:59 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>

# define INPUT_ERROR "Invalid number of arguments."
# define PIPE_ERROR "Pipe"
# define FORK_ERROR "Fork Failed"
# define CMD_ERROR "command not found"

typedef struct s_pipex
{
	int		infile_fd;
	int		outfile_fd;
	int		pipe_fd[2];
	int		pid1;
	int		pid2;
	int		in_err;
	int		out_err;
	int		pid1_err;
	int		pid2_err;
	char	*path;
	char	**command_paths;
	char	*command;
	char	**args;
}			t_pipex;

typedef struct s_quote
{
	int	open;
	int	close;
	int	q;
	int	i;
	int	j;
	int	len;
	int	count;
	int	flag;
}			t_quote;

char	**ft_split_pipex(char *s);
void	open_close(t_quote *quote, char *s);
void	count_flag(t_quote *quote, char c);
char	**get_word_space(t_quote *quote, char **arr, char *s);
char	**get_word_quote(t_quote *q, char **arr, char *s);

void	exit_perror(char *msg);
void	exit_err(char *msg, char *strerr, char *arg);
int		return_err(char *msg, char *strerr, char *arg);
void	close_fd(int x, int y);
void	free_command_path(t_pipex pipex);

char	*get_path(char **envp);
void	call_join(t_pipex *pipex);
int		check_args_in(t_pipex *pipex, int argc, char **argv);
int		check_args_out(t_pipex *pipex, int argc, char **argv);

void	call_pipe(t_pipex *pipex, char **envp);

#endif
