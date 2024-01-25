/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:29:14 by jberay            #+#    #+#             */
/*   Updated: 2024/01/25 12:29:15 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

char	*get_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp +5);
}

void	call_join(t_pipex *pipex)
{
	int		i;
	char	*tmp;

	i = -1;
	while (pipex->command_paths[++i])
	{
		tmp = ft_strjoin(pipex->command_paths[i], "/");
		if (!tmp)
		{
			free_struct(pipex);
			exit (1);
		}
		pipex->command = ft_strjoin(tmp, pipex->args[0]);
		if (!pipex->command)
		{
			free_struct(pipex);
			free(tmp);
			exit (1);
		}
		free (tmp);
		if (access(pipex->command, 0) == 0)
			pipex->path = ft_strdup(pipex->command);
		free (pipex->command);
	}
	free_split(pipex->command_paths);
}

void	check_args(t_pipex *pipex, int argc, char **argv)
{
	pipex->in_err = 0;
	pipex->out_err = 0;
	if (argc != 5)
	{
		ft_putstr_fd("zsh: ", 2);
		ft_putendl_fd(INPUT_ERROR, 2);
		exit (1);
	}
	pipex->in_fd = open(argv[1], O_RDONLY);
	if (pipex->in_fd == -1)
	{
		pipex->in_err = 1;
		args_err("zsh: ", strerror(errno), argv[1]);
	}
	pipex->out_fd = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0666);
	if (pipex->out_fd == -1)
	{
		pipex->out_err = 1;
		args_err("zsh: ", strerror(errno), argv[4]);
	}
	if (pipex->in_err && pipex->out_err)
		exit (pipex->out_err);
}

void	call_pipe(t_pipex *pipex, char **envp)
{
	if (pipe(pipex->pipe_fd) == -1)
		exit_perror(PIPE_ERROR);
	pipex->path = get_path(envp);
	pipex->command_paths = ft_split(pipex->path, ':');
	if (!pipex->command_paths)
		exit (1);
}
