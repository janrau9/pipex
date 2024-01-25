/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:28:24 by jberay            #+#    #+#             */
/*   Updated: 2024/01/25 12:28:26 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

void	cmd_err(char *msg, char *strerr, char **arg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(strerr, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(arg[0], 2);
	free_split(arg);
	exit (127);
}

void	args_err(char *msg, char *strerr, char *arg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(strerr, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(arg, 2);
}

void	exit_perror_exec(char *msg, char *path)
{
	perror(msg);
	if (path)
		free(path);
	exit (1);
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
