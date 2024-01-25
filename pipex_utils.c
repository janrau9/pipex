/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:30:30 by jberay            #+#    #+#             */
/*   Updated: 2024/01/25 08:29:15 by jberay           ###   ########.fr       */
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

	i = 0;
	while (pipex->command_paths[i])
	{
		tmp = ft_strjoin(pipex->command_paths[i], "/");
		pipex->command = ft_strjoin(tmp, pipex->args[0]);
		if (access(pipex->command, 0) == 0)
			pipex->path = pipex->command;
		i++;
	}
}

int	check_args_in(t_pipex *pipex, int argc, char **argv)
{
	if (argc != 5)
	{
		ft_putstr_fd("zsh: ", 2);
		ft_putendl_fd(INPUT_ERROR, 2);
		exit (1);
	}
	pipex->infile_fd = open(argv[1], O_RDONLY);
	if (pipex->infile_fd == -1)
		return (return_err("zsh: ", strerror(errno), argv[1]));
	return (0);
}

int	check_args_out(t_pipex *pipex, int argc, char **argv)
{
	pipex->outfile_fd = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0666);
	if (pipex->outfile_fd == -1)
		return (return_err("zsh: ", strerror(errno), argv[4]));
	return (0);
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