/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:45:46 by jberay            #+#    #+#             */
/*   Updated: 2024/01/22 10:27:00 by jberay           ###   ########.fr       */
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

static char	**word_split(char **arr, char const *s)
{
	size_t	i;
	size_t	j;
	size_t	len;
	int		open;
	int		close;
	int		q;

	q = 0;
	i = 0;
	j = 0;
	len = 0;
	open = 0;
	close = 0;
	while (s[i])
	{
		if (ft_strchr("\'\"", s[i]))
		{
			q++;
			if ((open == 0 && close == 0) && q % 2 == 1)
				open = 1;
			else if ((open == 1 && close == 0)
				&& ((ft_strchr("\'\"", s[i + 1]) && s[i + 1] == '\0') && q % 2 == 0))
				close = 1;
			else if (open == 1 && close == 1)
			{
				open = 0;
				close = 0;
			}
			i++;
		}

		if (!(open ^ close))
		{
			if (s[i] != ' ')
			{
				len = 0;
				while ((s[i + len] != ' ') && s[i + len] != '\0')
					len++;
				arr[j] = ft_substr(s, i, len);
				if (!arr[j])
					return (clear_array(arr, j));
				i = i + len;
				j++;
			}
			else
				i++;
		}
		else
		{
			while (!ft_strchr("\"\'", s[i + len]) && s[i + len] != '\0')
				len++;
			if (s[i + len] != 34 && s[i + len] != 39)
			{
				arr[j] = ft_substr(s, i - q, len + q);
				if (!arr[j])
					return (clear_array(arr, j));
				i = i + len;
				j++;
			}
			else
				len++;
		}
	}
	arr[j] = 0;
	j = 0;
	while (arr[j])
	{
		size_t s = ft_strlen(arr[j]);
		arr[j] = ft_strtrim(arr[j], "'");
		if (s == ft_strlen(arr[j]))
			arr[j] = ft_strtrim(arr[j], "\"");
		arr[j] = ft_strtrim(arr[j], " ");
		j++;
	}
	return (arr);
}

static void	open_close(t_quote *quote, char *s)
{
	if (ft_strchr("\'\"", *s))
	{
		quote->q++;
		if ((quote->open == 0 && quote->close == 0) && quote->q % 2 == 1)
			quote->open = 1;
		else if ((quote->open == 1 && quote->close == 0)
			&& (ft_strchr("\'\"", *s))
			&& ((*s + 1 != '\0') && quote->q % 2 == 0))
			quote->close = 1;
		else if (quote->open == 1 && quote->close == 1)
		{
			quote->open = 0;
			quote->close = 0;
		}
		quote->i++;
	}
}

static void	count_flag(t_quote *quote, char c)
{
	if (!(quote->open ^ quote->close))
	{
		if (c != ' ' && quote->flag == 0)
		{
			quote->flag = 1;
			quote->count++;
		}
		else if (c == ' ' && quote->flag == 1)
			quote->flag = 0;
	}
	else
	{
		if (quote->flag == 0)
		{
			quote->count++;
			quote->flag = 1;
		}
	}
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

char	**ft_split_pipex(char *s)
{
	char	**mptr;
	int		wc;
	t_quote	quote;

	quote.close = 0;
	quote.open = 0;
	quote.i = 0;
	quote.q = 0;
	quote.count = 0;
	quote.flag = 0;
	if (!s)
		return (NULL);
	wc = word_count(quote, s);
	mptr = malloc((wc + 1) * sizeof(char *));
	if (!mptr)
		return (0);
	quote.close = 0;
	quote.open = 0;
	quote.i = 0;
	quote.q = 0;
	quote.count = 0;
	quote.flag = 0;
	if (!word_split(mptr, s))
		return (NULL);
	return (mptr);
}