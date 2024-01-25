/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 08:43:08 by jberay            #+#    #+#             */
/*   Updated: 2024/01/25 08:32:55 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

void	pid2_child(t_pipex pipex, char **argv, char **envp)
{
	int	x;

	pipex.path = NULL;
	dup2(pipex.pipe_fd[0], STDIN_FILENO);
	dup2(pipex.outfile_fd, STDOUT_FILENO);
	close_fd(pipex.pipe_fd[0], pipex.pipe_fd[1]);
	close(pipex.outfile_fd);
	pipex.args = ft_split_pipex(argv[3]);
	if (!pipex.args)
		free_command_path(pipex);
	call_join(&pipex);
	if (pipex.path)
	{
		x = execve(pipex.path, pipex.args, envp);
		if (x == -1)
			exit_perror("Execve failed");
	}
	else
		exit_err("zsh: ", CMD_ERROR, pipex.args[0]);
}

void	pid1_child(t_pipex pipex, char **argv, char **envp)
{
	int	x;

	pipex.path = NULL;
	dup2(pipex.pipe_fd[1], STDOUT_FILENO);
	dup2(pipex.infile_fd, STDIN_FILENO);
	close_fd(pipex.pipe_fd[0], pipex.pipe_fd[1]);
	close(pipex.infile_fd);
	pipex.args = ft_split_pipex(argv[2]);
	if (!pipex.args)
		free_command_path(pipex);
	call_join(&pipex);
	if (pipex.path)
	{
		x = execve(pipex.path, pipex.args, envp);
		if (x == -1)
			exit_perror("Execve failed");
	}
	else
		exit_err("zsh: ", CMD_ERROR, pipex.args[0]);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		wstatus1;
	int		wstatus2;

	pipex.in_err = check_args_in(&pipex, argc, argv);
	pipex.out_err = check_args_out(&pipex, argc, argv);
	if (pipex.in_err && pipex.out_err)
		return (pipex.out_err);
	call_pipe(&pipex, envp);
	if (!pipex.in_err)
	{
		pipex.pid1 = fork();
		if (pipex.pid1 == -1)
			exit_perror(FORK_ERROR);
		if (pipex.pid1 == 0)
			pid1_child(pipex, argv, envp);
	}
	if (!pipex.out_err)
	{
		pipex.pid2 = fork();
		if (pipex.pid2 == -1)
			exit_perror(FORK_ERROR);
		if (pipex.pid2 == 0)
			pid2_child(pipex, argv, envp);
	}
	close_fd(pipex.pipe_fd[0], pipex.pipe_fd[1]);
	waitpid(pipex.pid1, &wstatus1, 0);
	if (WIFEXITED(wstatus1))
	{
		if (!WEXITSTATUS(wstatus1))
		{
			pipex.pid1_err = 0;
			printf("succes b4 1 %d \n", pipex.pid1_err);
		}
		else
		{
			pipex.pid1_err = WEXITSTATUS(wstatus1);
			printf("failed b4 1 %d \n", pipex.pid1_err);
		}
	}
	waitpid(pipex.pid2, &wstatus2, 0);
	if (WIFEXITED(wstatus2))
	{
		printf("pid 2 %d \n", wstatus2);
		if (!WEXITSTATUS(wstatus2))
		{
			pipex.pid2_err = 0;
			printf("success b4 2 %d \n", pipex.pid2_err);
		}
		else
		{
			pipex.pid2_err = WEXITSTATUS(wstatus2);
			printf("failed b4 2 %d \n", WEXITSTATUS(wstatus2));
		}
	}
	printf("a 1 %d \n", pipex.pid1_err);
	printf("a 2 %d \n", pipex.pid2_err);
	if (!pipex.out_err)
		return (pipex.pid2_err);
	else
		return (pipex.out_err);
	return (0);
}
