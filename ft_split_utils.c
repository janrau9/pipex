/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:18:55 by jberay            #+#    #+#             */
/*   Updated: 2024/01/22 11:18:56 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
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

void	count_flag(t_quote *quote, char c)
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

void	open_close(t_quote *quote, char *s)
{
	if (ft_strchr("\'\"", *s))
	{
		quote->q++;
		if ((quote->open == 0 && quote->close == 0) && quote->q % 2 == 1)
			quote->open = 1;
		else if ((quote->open == 1 && quote->close == 0)
			&& (ft_strchr("\'\"", *s + 1))
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

char	**get_word_quote(t_quote *q, char **arr, char *s)
{
	while (!ft_strchr("\"\'", s[q->i + q->len])
		&& (s[q->i + q->len] != '\0'))
		q->len++;
	if (s[q->i + q->len] != 34 && s[q->i + q->len] != 39)
	{
		arr[q->j] = ft_substr(s, q->i - q->q, q->len + q->q);
		if (!arr[q->j])
			return (clear_array(arr, q->j));
		q->i = q->i + q->len;
		q->j++;
	}
	else
		q->len++;
	return (arr);
}

char	**get_word_space(t_quote *quote, char **arr, char *s)
{
	if (s[quote->i] != ' ')
	{
		quote->len = 0;
		while ((s[quote->i + quote->len] != ' ')
			&& (s[quote->i + quote->len] != '\0'))
			quote->len++;
		arr[quote->j] = ft_substr(s, quote->i, quote->len);
		if (!arr[quote->j])
			return (clear_array(arr, quote->j));
		quote->i = quote->i + quote->len;
		quote->j++;
	}
	else
		quote->i++;
	return (arr);
}
