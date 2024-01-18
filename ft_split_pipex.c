/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 08:07:18 by jberay            #+#    #+#             */
/*   Updated: 2024/01/18 08:44:18 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

static char	**clear_array(char **s, size_t j)
{
	while (j > 0)
	{
		free(s[j -1]);
		j--;
	}
	free(s);
	return (NULL);
}

static char	**word_split(char **arr, char const *s, char *reject)
{
	size_t	i;
	size_t	j;
	size_t	len;
	int		chk;

	i = 0;
	j = 0;
	len = 0;
	chk = 0;
	while (s[i])
	{
		if (!ft_strchr(reject, s[i]))
		{
			len = 0;
			while (!ft_strchr(reject, s[i + len]) && s[i + len] != '\0')
			{
				if (ft_strchr("'", s[i]))
					chk++;
				len++;
			}
			arr[j] = ft_substr(s, i, len);
			if (!arr[j])
				return (clear_array(arr, j));
			i = i + len;
			j++;
		}
		else
			i++;
	}
	arr[j] = 0;
	return (arr);
}

static size_t	word_count(char const *s, char *reject)
{
	int		flag;
	int		chk;
	size_t	count;
	int		i;

	flag = 0;
	count = 0;
	i = 0;
	chk = 0;
	while (s[i])
	{
		if (!ft_strchr(reject, s[i]) && flag && chk % 2 == 0)
		{
			if (ft_strchr("'", s[i]))
				chk++;
			flag = 1;
			count++;
		}
		else if (ft_strchr(reject, s[i]) && flag == 1)
			flag = 0;
		i++;
	}
	return (count);
}

/**
 * @brief divide string into double array with the given delimiter
 * 
 * @param s string
 * @param c delimeter
 * @return char** 
 */
char	**ft_split_pipex(char const *s, char *reject)
{
	char	**mptr;

	if (!s)
		return (NULL);
	mptr = malloc((word_count(s, reject) + 1) * sizeof(char *));
	if (!mptr)
		return (0);
	if (!word_split(mptr, s, reject))
		return (NULL);
	return (mptr);
}
