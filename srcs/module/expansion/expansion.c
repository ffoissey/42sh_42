/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 00:58:53 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	character_swap(const char swapped)
{
	static char previous = '\0';
	char		c;

	c = previous;
	previous = swapped;
	return (c);
}

int		check_backslash(char *dest, t_quote quote, int i)
{
	if (quote == QUOTE_DOUBLE)
	{
		if (ft_strchr(BACKSLASH_DQUOTE, dest[i + 1]))
			return (i + 1);
		else
			return (i);
	}
	else
		return (i + 1);
}

void	newline_removal(char *str)
{
	t_quote		quote;

	quote = 0;
	while (*str != '\0')
	{
		if (ft_strchr("\'\"", *str))
			quote = select_quoting(quote, *str);
		if (*str == '\n' && quote == QUOTE_OFF)
			delete_character(str);
		++str;
	}
}

char	*expansion_pipeline(t_list *intern_var, char *str)
{
	char		*dest;
	char		*expanded;

	newline_removal(str);
	if ((dest = tilde(intern_var, str)) == NULL)
		return (NULL);
	expanded = variable_expansion(intern_var, dest);
	ft_strdel(&dest);
	if (expanded == NULL)
		return (NULL);
	dest = arithmetic_expansion(expanded);
	ft_strdel(&expanded);
	if (dest == NULL)
		return (NULL);
	quote_removal(dest);
	return (dest);
}

char	*expansion_word(t_list *intern_var, char *str)
{
	char		*dest;
	char		*expanded;

	newline_removal(str);
	if ((dest = tilde(intern_var, str)) == NULL)
		return (NULL);
	expanded = variable_expansion(intern_var, dest);
	ft_strdel(&dest);
	if (expanded == NULL)
		return (NULL);
	dest = arithmetic_expansion(expanded);
	ft_strdel(&expanded);
	if (dest == NULL)
		return (NULL);
	return (dest);
}
