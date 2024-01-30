/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:18:29 by jberay            #+#    #+#             */
/*   Updated: 2024/01/30 11:31:59 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**word_split(t_quote quote, char **arr, char *s)
{
	size_t	len;
	int		j;

	while (s[quote.i])
	{
		open_close(&quote, &s[quote.i]);
		if (!(quote.open ^ quote.close))
			arr = get_word_space(&quote, arr, s);
		else
			arr = get_word_quote(&quote, arr, s);
	}
	arr[quote.j] = 0;
	j = 0;
	while (arr[j])
	{
		len = ft_strlen(arr[j]);
		arr[j] = ft_strtrim(arr[j], "'");
		if (len == ft_strlen(arr[j]))
			arr[j] = ft_strtrim(arr[j], "\"");
		arr[j] = ft_strtrim(arr[j], " ");
		j++;
	}
	return (arr);
}

static size_t	word_count(t_quote quote, char *s)
{
	while (s[quote.i])
	{
		open_close(&quote, &s[quote.i]);
		count_flag(&quote, s[quote.i]);
		quote.i++;
	}
	return (quote.count);
}

static void	init_struct(t_quote *quote)
{
	quote->close = 0;
	quote->open = 0;
	quote->i = 0;
	quote->q = 0;
	quote->j = 0;
	quote->count = 0;
	quote->flag = 0;
	quote->len = 0;
}

char	**ft_split_pipex(char *s)
{
	char	**mptr;
	int		wc;
	t_quote	quote;

	init_struct(&quote);
	if (!s)
		return (NULL);
	wc = word_count(quote, s);
	mptr = malloc((wc + 1) * sizeof(char *));
	if (!mptr)
		return (0);
	if (!word_split(quote, mptr, s))
		return (NULL);
	return (mptr);
}
