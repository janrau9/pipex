/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:12:59 by jberay            #+#    #+#             */
/*   Updated: 2024/01/22 11:01:09 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include <stdio.h>

int	main(void)
{
	char	**result;
	int		i;

	// result = ft_split_pipex("awk \'{count++} END {print count}\'", ' ');
	result = ft_split_pipex("awk '{c++} END {print c}'");
	i = 0;
	printf("%s \n","awk '{count++} END {print count}'");
	while (result[i])
	{
		printf("%s\n", result[i]);
		i++;
	}
	printf("%s\n", result[i]);
	
}