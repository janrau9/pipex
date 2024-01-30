/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:28:24 by jberay            #+#    #+#             */
/*   Updated: 2024/01/30 11:51:38 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd_err(char *msg, char *strerr, char **arg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(strerr, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(arg[0], 2);
	if (arg)
		free_split(arg);
	exit (127);
}

void	empty_err(char *msg, char *strerr, char **arg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(strerr, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg[0], 2);
	ft_putchar_fd('\n', 2);
	if (arg)
		free_split(arg);
	exit (1);
}

void	exec_err(char *msg, char *path, char **arg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(path, 2);
	if (path)
		free(path);
	if (arg)
		free_split(arg);
	exit (1);
}

void	args_err(char *msg, char *strerr, char *arg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(strerr, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(arg, 2);
}

void	exit_perror(char *msg)
{
	perror(msg);
	exit (1);
}
