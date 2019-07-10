/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 22:43:18 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 17:10:07 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		del_arithmetic(t_arithmetic *arithmetic, char **output)
{
	ft_strdel(output);
	vct_del(&arithmetic->input);
	ft_strdel(&arithmetic->expanded);
	ft_lstdel(&arithmetic->tokens, del_token);
	ft_lstdel(&arithmetic->solving, NULL);
	ft_lstdelone(&arithmetic->current, del_token);
	ft_stckdestroy(&arithmetic->processing, del_token);
	return (FAILURE);
}

void	del_infix(t_infix *infix)
{
	ft_stckdestroy(&infix->calcul, NULL);
}

void	m_get_token(t_arithmetic *arithmetic, t_list **node)
{
	if (node)
		ft_lstdel(node, NULL);
	arithmetic->current = arithmetic->tokens;
	arithmetic->tokens = arithmetic->tokens->next;
	arithmetic->current->next = NULL;
	arithmetic->curr_token = arithmetic->current->data;
}

int8_t	get_expansion_input(t_arithmetic *arithmetic, char *input, size_t start)
{
	char		*str;

	str = NULL;
	ft_asprintf(&str, "%.*s", arithmetic->end - start - 2, input + start);
	if (str == NULL)
	{
		ft_dprintf(2, "Malloc Error on get_expansion_input\n");
		return (FAILURE);
	}
	if (ft_strchr(str, '.'))
	{
		ft_dprintf(2, "42sh: .: syntax error\n");
		ft_strdel(&str);
		return (FAILURE);
	}
	arithmetic->input = vct_dups(str);
	ft_strdel(&str);
	return (SUCCESS);
}

int8_t	find_expansion_end(t_arithmetic *arithmetic, char *input, size_t start)
{
	size_t		end;
	size_t		parent;

	end = start;
	parent = 2;
	while (input[end])
	{
		if (parent == 0)
		{
			arithmetic->end = end;
			return (SUCCESS);
		}
		else if (input[end] == '(')
			parent++;
		else if (input[end] == ')')
			parent--;
		end++;
	}
	if (parent == 0)
	{
		arithmetic->end = end;
		return (SUCCESS);
	}
	ft_dprintf(2, "42sh: Unexpected EOF while testing\n");
	return (FAILURE);
}
