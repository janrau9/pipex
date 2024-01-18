/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 08:48:49 by jberay            #+#    #+#             */
/*   Updated: 2024/01/18 11:43:32 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

char	**parser(char *str)
{
	int		i;
	int		j;
	int		q;
	char	*tmp;
	t_list	*head;

	q = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == 39)
			q++;
		if (str[i + 1] != ' ' && str[i] != 39)
		{
			tmp[j] = str[i];
		}
		else if (str[i + 1] == ' ')
		{
			tmp[j] = str[i];
			tmp[j + 1] = '/0';
			head = ft_lstnew(tmp);
			j = -1;
		}
		i++;
		j++;
	}
}