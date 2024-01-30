/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 08:47:22 by jberay            #+#    #+#             */
/*   Updated: 2024/01/30 16:33:23 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>

# define INPUT_ERROR "Invalid number of arguments."
# define PIPE_ERROR "Pipe Failed"
# define FORK_ERROR "Fork Failed"
# define CMD_ERROR "command not found"
# define EMPTY_ERROR "permission denied"

typedef struct s_pipex
{
	int		in_fd;
	int		out_fd;
	int		pipe_fd[2];
	int		pid1;
	int		pid2;
	int		in_err;
	int		out_err;
	int		pid1_err;
	int		pid2_err;
	int		wait_status;
	int		join;
	char	*tmp;
	char	*path;
	char	**command_paths;
	char	*command;
	char	**args;
}			t_pipex;

void	exit_perror_exec(char *msg, char *path);
void	exit_perror(char *msg);
void	cmd_err(char *msg, char *strerr, char **arg);
void	args_err(char *msg, char *strerr, char *arg);
void	exec_err(char *msg, char *path, char **arg);
void	empty_err(char *msg, char *strerr, char **arg);

void	close_fd(int x, int y);
void	free_split(char **args);
void	exit_free_struct(t_pipex *pipex);
void	exit_free_split(char **args);

char	*get_path(char **envp);
void	call_join(t_pipex *pipex);
void	check_args(t_pipex *pipex, int argc, char **argv);

void	call_pipe(t_pipex *pipex, char **envp);

#endif
