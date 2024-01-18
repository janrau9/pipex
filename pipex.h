/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 08:47:22 by jberay            #+#    #+#             */
/*   Updated: 2024/01/18 08:54:52 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>

# define INPUT_ERROR "Invalid number of arguments.\n"
# define INFILE_ERROR "Infile"
# define OUTFILE_ERROR "Outfile"
# define PIPE_ERROR "Pipe"
# define FORK_ERROR "Fork Failed"
# define CMD_ERROR "Command not found\n"

typedef struct s_pipex
{
	int		infile_fd;
	int		outfile_fd;
	int		pipe_fd[2];
	int		pid1;
	int		pid2;
	char	*path;
	char	**command_paths;
}			t_pipex;

char	**ft_split_pipex(char const *s, char *reject);

#endif
