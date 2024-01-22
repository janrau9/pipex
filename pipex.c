/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 08:43:08 by jberay            #+#    #+#             */
/*   Updated: 2024/01/22 09:55:18 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"
# include <stdio.h>

void	error_msg(char *msg)
{
	ft_putendl_fd(msg, 2);
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
	// char	*args[] = {"awk", "{c++} END {print c}", NULL};
	char	**args;
	
	int		i;
	char	*tmp;
	char	*path;
	char	*command;

	path = NULL;

	// (void)argv;

	dup2(pipex.pipe_fd[0], STDIN_FILENO);
	dup2(pipex.outfile_fd, STDOUT_FILENO);
	close(pipex.pipe_fd[0]);
	close(pipex.pipe_fd[1]);
	close(pipex.outfile_fd);
	args = ft_split_pipex(argv[3]);
	if (!args)
		return ;
	
	// printf("%s \n", argv[3]);
	// int k = 0;
	// while (args[k])
	// {
	// 	printf("args - %s \n", args[k]);
	// 	k++;
	// }

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
	{
		int x = execve(path, args, envp);
		if (x == -1)
		{
			printf("%d \n", x);
			perror("Execve failed");
			exit(errno);
		}
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

	path = NULL;
	dup2(pipex.pipe_fd[1], STDOUT_FILENO);
	dup2(pipex.infile_fd, STDIN_FILENO);
	close(pipex.pipe_fd[1]);
	close(pipex.pipe_fd[0]);
	close(pipex.infile_fd);
	args = ft_split(argv[2], ' ');
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
	{
		int x = execve(path, args, envp);
		if (x == -1)
		{
			perror("Execve failed");
			exit(errno);
		}
		}
	else
		error_msg(CMD_ERROR);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
	{
		error_msg(INPUT_ERROR);
	}
	pipex.infile_fd = open(argv[1], O_RDONLY);
	if (pipex.infile_fd == -1)
	{
		perror(INFILE_ERROR);
		return (0);
	}
	pipex.outfile_fd = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0666);
	if (pipex.outfile_fd == -1)
	{
		perror(OUTFILE_ERROR);
		return (1);
	}
	if (pipe(pipex.pipe_fd) == -1)
		return (errno);
	pipex.path = get_path(envp);
	pipex.command_paths = ft_split(pipex.path, ':');
	if (!pipex.command_paths)
		return (errno);
	pipex.pid1 = fork();
	if (pipex.pid1 == -1)
		return (errno);
	if (pipex.pid1 == 0)
		pid1_child(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == -1)
		return (errno);
	if (pipex.pid2 == 0)
		pid2_child(pipex, argv, envp);
	close(pipex.pipe_fd[0]);
	close(pipex.pipe_fd[1]);
	waitpid(pipex.pid1, NULL, 0);
	int wstatus;
	waitpid(pipex.pid2, &wstatus, 0);
	if (WIFEXITED(wstatus))
	{
		int statuscode = WEXITSTATUS(wstatus);
		if (statuscode == 0)
			return(wstatus);
		else
			return(2);
	}
	return (0);
}