/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 08:43:08 by jberay            #+#    #+#             */
/*   Updated: 2024/01/18 11:50:01 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"
# include <stdio.h>

void	error_msg(char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit (1);
}

void	perror_msg(char *msg)
{
	perror(msg);
	exit (1);
}
char	*get_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp +5);
}

void pid2_child(t_pipex pipex, char **argv, char **envp)
{
	// char	*args[] = {"awk", "{count++}" "END" "{print" "count}", NULL};
	char	**args;
	int		i;
	char	*tmp;
	char	*path;
	char	*command;
	// char	*reject = " ";
	path = NULL;

	dup2(pipex.pipe_fd[0], STDIN_FILENO);
	// dup2(pipex.outfile_fd, STDOUT_FILENO);
	close(pipex.pipe_fd[0]);
	close(pipex.pipe_fd[1]);
	close(pipex.outfile_fd);
	args = ft_split(argv[3], ' ');
	if (!args)
		return ;
	i = 0;
	
	int k = 0;
	while (args[k])
	{
		printf("args - %s \n", args[k]);
		k++;
	}



	while (pipex.command_paths[i])
	{
		tmp = ft_strjoin(pipex.command_paths[i], "/");
		command = ft_strjoin(tmp, args[0]);
		if (access(command, 0) == 0)
			path = command;
		i++;
	}
	if (path)
	{
		printf("%s \n", path);
		printf("%s %s\n", args[0], args[1]);
		int j = execve(path, args, envp);
		printf("%d \n", j);
	}
	else
		error_msg(CMD_ERROR);
}

void pid1_child(t_pipex pipex, char **argv, char **envp)
{
	char	**args;
	int		i;
	char	*tmp;
	char	*path;
	char	*command;
	char	*reject = "\"\' ";

	path = NULL;
	dup2(pipex.pipe_fd[1], STDOUT_FILENO);
	dup2(pipex.infile_fd, STDIN_FILENO);
	close(pipex.pipe_fd[1]);
	close(pipex.pipe_fd[0]);
	close(pipex.infile_fd);
	args = ft_split_pipex(argv[2], reject);
	if (!args)
		return ;
	i = 0;
	while (pipex.command_paths[i])
	{
		tmp = ft_strjoin(pipex.command_paths[i], "/");
		command = ft_strjoin(tmp, args[0]);
		if (access(command, 0) == 0)
			path = command;
		i++;
	}
	if (path)
		execve(path, args, envp);
	else
		error_msg(CMD_ERROR);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		error_msg(INPUT_ERROR);
	pipex.infile_fd = open(argv[1], O_RDONLY, 0644);
	if (pipex.infile_fd == -1)
		perror_msg(INFILE_ERROR);
	pipex.outfile_fd = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (pipex.outfile_fd == -1)
		perror_msg(OUTFILE_ERROR);
	if (pipe(pipex.pipe_fd) == -1)
		exit (-1);
	pipex.path = get_path(envp);
	pipex.command_paths = ft_split(pipex.path, ':');
	if (!pipex.command_paths)
		return (1);
	pipex.pid1 = fork();
	if (pipex.pid1 == -1)
		exit (-1);
	if (pipex.pid1 == 0)
		pid1_child(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == -1)
		exit (-1);
	if (pipex.pid2 == 0)
		pid2_child(pipex, argv, envp);
	// close(pipex.pipe_fd[0]);
	// close(pipex.pipe_fd[1]);
	// waitpid(pipex.pid1, NULL, 0);
	// waitpid(pipex.pid2, NULL, 0);
	return (0);
}