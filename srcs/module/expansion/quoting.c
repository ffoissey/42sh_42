/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 20:16:09 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		delete_character(char *str)
{
	char	holder;

	while (str[1] != '\0')
	{
		holder = str[0];
		str[0] = str[1];
		str[1] = holder;
		++str;
	}
	*str = '\0';
}

static int	delete_backslash(char *str, t_quote quote)
{
	if (quote == QUOTE_DOUBLE)
	{
		if (ft_strchr(BACKSLASH_DQUOTE, str[1]))
		{
			delete_character(str);
			return (TRUE);
		}
		else
			return (TRUE);
	}
	else
	{
		delete_character(str);
		return (*str == '\"' || *str == '\'' ? TRUE : FALSE);
	}
}

static int	delete_newline(char *str)
{
	delete_character(str);
	delete_character(str);
	return (TRUE);
}

t_quote		select_quoting(t_quote quote, const char c)
{
	if (quote == QUOTE_OFF)
		quote = c == '\'' ? QUOTE_SINGLE : QUOTE_DOUBLE;
	else if (quote == QUOTE_SINGLE)
		quote = c == '\'' ? QUOTE_OFF : QUOTE_SINGLE;
	else if (quote == QUOTE_DOUBLE)
		quote = c == '\"' ? QUOTE_OFF : QUOTE_DOUBLE;
	return (quote);
}

void		quote_removal(char *str)
{
	t_quote		quote;

	quote = 0;
	while (*str != '\0')
	{
		if (ft_strchr("\'\"", *str))
			quote = select_quoting(quote, *str);
		if (ft_strnequ("\\\n", str, 2) && (quote != QUOTE_SINGLE))
		{
			if (delete_newline(str) == TRUE)
				str++;
		}
		if (*str == '\\' && (quote != QUOTE_SINGLE))
		{
			if (delete_backslash(str, quote) == TRUE)
				str++;
		}
		if (quote != QUOTE_DOUBLE && *str == '\'')
			delete_character(str);
		else if (quote != QUOTE_SINGLE && *str == '\"')
			delete_character(str);
		else
			++str;
	}
}
