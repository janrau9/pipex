/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 07:40:07 by jberay            #+#    #+#             */
/*   Updated: 2024/01/19 07:57:03 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"
#include <stdio.h>

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

static char	**word_split(char **arr, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	len;
	int		flag;

	i = 0;
	j = 0;
	flag = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] != c || flag == 1)
		{
			len = 0;
			while (s[i] == ' ')
				i++;
			while ((s[i + len] != c || flag == 1) && s[i + len] != '\0')
				len++;
			arr[j] = ft_substr(s, i, len);
			if (!arr[j])
				return (clear_array(arr, j));
			i = i + len;
			j++;
		}
		else
			i++;
		flag = 1;
	}
	arr[1] = ft_strtrim(arr[1], "'");
	arr[j] = 0;
	return (arr);
}

// static size_t	word_count(char const *s, char c)
// {
// 	int		flag;
// 	size_t	count;
// 	int		i;

// 	flag = 0;
// 	count = 0;
// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] != c && flag == 0)
// 		{
// 			flag = 1;
// 			count++;
// 		}
// 		else if (s[i] == c && flag == 1)
// 			flag = 0;
// 		i++;
// 	}
// 	return (count);
// }

/**
 * @brief divide string into double array with the given delimiter
 * 
 * @param s string
 * @param c delimeter
 * @return char** 
 */
char	**ft_split_two(char const *s, char c)
{
	char	**mptr;

	if (!s)
		return (NULL);
	mptr = malloc((3) * sizeof(char *));
	if (!mptr)
		return (0);
	if (!word_split(mptr, s, c))
		return (NULL);
	return (mptr);
}
