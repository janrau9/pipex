/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 08:43:08 by jberay            #+#    #+#             */
/*   Updated: 2024/01/30 11:53:02 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pid2_child(t_pipex pipex, char **argv, char **envp)
{
	pipex.path = NULL;
	dup2(pipex.pipe_fd[0], STDIN_FILENO);
	dup2(pipex.out_fd, STDOUT_FILENO);
	close_fd(pipex.pipe_fd[0], pipex.pipe_fd[1]);
	close_fd(pipex.in_fd, pipex.out_fd);
	pipex.args = ft_split_pipex(argv[3]);
	if (!pipex.args)
	{
		free_split(pipex.command_paths);
		exit (1);
	}
	if (pipex.args[0] == 0)
		empty_err("Pipex: ", EMPTY_ERROR, pipex.args);
	if (access(pipex.args[0], 0) == 0)
		pipex.path = ft_strdup(pipex.args[0]);
	else
		call_join(&pipex);
	if (pipex.path)
	{
		if ((execve(pipex.path, pipex.args, envp)) < 0)
			exec_err("Pipex: ", pipex.path, pipex.args);
	}
	else
		cmd_err("Pipex: ", CMD_ERROR, pipex.args);
}

void	pid1_child(t_pipex pipex, char **argv, char **envp)
{
	pipex.path = NULL;
	dup2(pipex.pipe_fd[1], STDOUT_FILENO);
	dup2(pipex.in_fd, STDIN_FILENO);
	close_fd(pipex.pipe_fd[0], pipex.pipe_fd[1]);
	close_fd(pipex.in_fd, pipex.out_fd);
	pipex.args = ft_split_pipex(argv[2]);
	if (!pipex.args)
	{
		free_split(pipex.command_paths);
		exit (1);
	}
	if (pipex.args[0] == 0)
		empty_err("Pipex: ", EMPTY_ERROR, pipex.args);
	if (access(pipex.args[0], 0) == 0)
		pipex.path = ft_strdup(pipex.args[0]);
	else
		call_join(&pipex);
	if (pipex.path)
	{
		if ((execve(pipex.path, pipex.args, envp)) < 0)
			exec_err("Pipex: ", pipex.path, pipex.args);
	}
	else
		cmd_err("Pipex: ", CMD_ERROR, pipex.args);
}

static void	call_fork_one(t_pipex *pipex, char **argv, char **envp)
{
	pipex->pid1 = fork();
	if (pipex->pid1 == -1)
	{
		free_split(pipex->command_paths);
		exit_perror(FORK_ERROR);
	}
	if (pipex->pid1 == 0)
		pid1_child(*pipex, argv, envp);
}

static void	call_fork_two(t_pipex *pipex, char **argv, char **envp)
{
	pipex->pid2 = fork();
	if (pipex->pid2 == -1)
	{
		free_split(pipex->command_paths);
		exit_perror(FORK_ERROR);
	}
	if (pipex->pid2 == 0)
		pid2_child(*pipex, argv, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	check_args(&pipex, argc, argv);
	call_pipe(&pipex, envp);
	if (!pipex.in_err)
		call_fork_one(&pipex, argv, envp);
	if (!pipex.out_err)
		call_fork_two(&pipex, argv, envp);
	free_split(pipex.command_paths);
	close_fd(pipex.pipe_fd[0], pipex.pipe_fd[1]);
	close_fd(pipex.in_fd, pipex.out_fd);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, &pipex.wait_status, 0);
	if (WIFEXITED(pipex.wait_status))
	{
		if (!WEXITSTATUS(pipex.wait_status))
			pipex.pid2_err = 0;
		else
			pipex.pid2_err = WEXITSTATUS(pipex.wait_status);
	}
	if (!pipex.out_err)
		return (pipex.pid2_err);
	else
		return (pipex.out_err);
	return (0);
}
