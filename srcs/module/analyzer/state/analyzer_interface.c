/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_interface.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 17:01:44 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		check_token(t_analyze *analyze)
{
	if (analyze->tokens == NULL)
		return (0);
	if (analyze->token.type == E_SEMICOLON)
		return (0);
	if (analyze->token.type == E_PIPE)
		return (0);
	if (analyze->token.type == E_END)
		return (0);
	if (analyze->token.type == E_NEWLINE)
		return (0);
	return (1);
}

void	error_analyzer(t_analyze *analyze)
{
	if (analyze->valid == -2)
		ft_dprintf(2, "42sh: ambiguous redirect\n");
	else
	{
		ft_dprintf(2, "42sh: analyze error near unexpected token `%s'\n",
				g_shell->grammar[analyze->token.type]);
	}
	analyze->state = P_ERROR;
	analyze->valid = -1;
	ft_strdel(&analyze->token.data);
	ft_stckdestroy(&analyze->stack, del_token);
	ft_stckdestroy(&analyze->tree_node, del_action);
	ft_lstdel(analyze->tokens, del_token);
}

void	stop_analyzer(t_analyze *analyze)
{
	t_action	action;

	analyze->state = P_STOP;
	if (analyze->valid == 1)
	{
		ft_bzero(&action, sizeof(t_action));
		if (analyze->token.type == E_DAND)
			action.type = A_DAND;
		else if (analyze->token.type == E_OR)
			action.type = A_OR;
		else if (analyze->token.type == E_SEMICOLON)
			action.type = A_END;
		else if (analyze->token.type == E_NEWLINE)
			action.type = A_END;
		else if (analyze->token.type == E_AND)
			action.type = A_AND;
		ft_stckpush(&analyze->tree_node, &action, sizeof(t_action));
		analyze->valid = 0;
	}
	get_token(analyze);
}

void	end_analyzer(t_analyze *analyze)
{
	t_action	action;

	analyze->state = P_END;
	if (analyze->valid == 1)
	{
		ft_bzero(&action, sizeof(t_action));
		action.type = A_END;
		ft_stckpush(&analyze->tree_node, &action, sizeof(t_action));
	}
	get_token(analyze);
}
