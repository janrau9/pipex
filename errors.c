/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:05:42 by jberay            #+#    #+#             */
/*   Updated: 2024/01/25 08:04:27 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"


void	exit_err(char *msg, char *strerr, char *arg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(strerr, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(arg, 2);
	exit (127);
}

int	return_err(char *msg, char *strerr, char *arg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(strerr, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(arg, 2);
	return (1);
}

void	exit_perror(char *msg)
{
	perror(msg);
	exit (1);
}

void	close_fd(int x, int y)
{
	close(x);
	close(y);
}

void	free_command_path(t_pipex pipex)
{
	int	i;

	i = 0;
	while (pipex.command_paths[i])
	{
		free(pipex.command_paths[i]);
		i--;
	}
	free(pipex.command_paths);
}
