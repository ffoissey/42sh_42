/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_analyzer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 21:48:28 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <fcntl.h>
#include <unistd.h>

void		heredoc_delimiter(t_analyze *analyze)
{
	if (analyze->state == P_HEREDOC_REDIRECT)
		analyze->state = P_HEREDOC_DELIMITER;
	else
		analyze->state = P_IO_HEREDOC_DELIMITER;
	if ((g_shell->option.option & INTERACTIVE_OPT) == FALSE)
	{
		ft_dprintf(2, "42sh: Here documents only in interractive mode\n");
		ft_lstdel(analyze->tokens, del_token);
		ft_strdel(&analyze->token.data);
		error_analyzer(analyze);
	}
	analyze->token.type = E_STRING;
	ft_stckpush(&analyze->stack, &analyze->token, sizeof(t_token));
	get_token(analyze);
}

void		io_heredoc_analyzer(t_analyze *analyze)
{
	t_list			*node;
	t_action		action;
	enum e_type		type;

	analyze->state = P_IO_HEREDOC;
	ft_bzero(&action, sizeof(t_action));
	node = ft_stckpopnode(&analyze->stack);
	ft_lstaddback(&action.data, node);
	node = ft_stckpopnode(&analyze->stack);
	type = ((t_token *)node->data)->type;
	if (type == E_DLESS)
		action.type = A_IO_HEREDOC;
	else if (type == E_DLESSDASH)
		action.type = A_IO_HEREDOC_TRIM;
	ft_lstdelone(&node, NULL);
	node = ft_stckpopnode(&analyze->stack);
	ft_lstaddback(&action.data, node);
	ft_stckpush(&analyze->tree_node, &action, sizeof(t_action));
}

void		heredoc_analyzer(t_analyze *analyze)
{
	t_list			*node;
	t_action		action;
	enum e_type		type;

	analyze->state = P_HEREDOC;
	ft_bzero(&action, sizeof(t_action));
	node = ft_stckpopnode(&analyze->stack);
	ft_lstaddback(&action.data, node);
	node = ft_stckpopnode(&analyze->stack);
	type = ((t_token *)node->data)->type;
	if (type == E_DLESS)
		action.type = A_HEREDOC;
	else if (type == E_DLESSDASH)
		action.type = A_HEREDOC_TRIM;
	ft_lstdelone(&node, NULL);
	ft_stckpush(&analyze->tree_node, &action, sizeof(t_action));
}
