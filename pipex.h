/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 08:47:22 by jberay            #+#    #+#             */
/*   Updated: 2024/01/22 10:26:41 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <errno.h>
# include <string.h>

# define INPUT_ERROR "Invalid number of arguments.\n"
# define INFILE_ERROR "Pipex"
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

typedef struct s_quote
{
	int	open;
	int	close;
	int	q;
	int	i;
	int	j;
	int	len;
	int	count;
	int	flag;
}			t_quote;

char	**ft_split_pipex(char *s);
// void	open_close(t_quote *quote, char *s);

#endif
