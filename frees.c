/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:23:12 by jberay            #+#    #+#             */
/*   Updated: 2024/01/30 11:32:01 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_struct(t_pipex *pipex)
{
	free_split(pipex->command_paths);
	pipex->command_paths = NULL;
	free_split(pipex->args);
	pipex->args = NULL;
}

void	close_fd(int x, int y)
{
	close(x);
	close(y);
}
