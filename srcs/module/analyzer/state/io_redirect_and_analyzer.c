/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirect_and_analyzer.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:15:21 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int				define_io_dup_move(t_token *token)
{
	int		len;
	int		index;
	int		tester;

	len = ft_strlen(token->data);
	index = 0;
	tester = 0;
	if (len == 1 && token->data[0] == '-')
		return (A_CLOSE);
	while (index < len - 1)
	{
		if (ft_isdigit(token->data[index++]) == 0)
			return (A_AMBIGOUS_REDIRECT);
	}
	if (token->data[len - 1] == '-')
		return (A_MOVE);
	else if (ft_isdigit(token->data[len - 1]))
		return (A_DUP);
	else
		return (A_AMBIGOUS_REDIRECT);
}

void			io_and_redirect_flush(t_analyze *analyze)
{
	enum e_type type;
	t_list		*node;
	t_action	action;

	analyze->state = P_IO_FLUSH_AND;
	ft_bzero(&action, sizeof(t_action));
	node = ft_stckpopnode(&analyze->stack);
	if ((action.type = define_io_dup_move(node->data)) == A_AMBIGOUS_REDIRECT)
	{
		analyze->valid = -2;
		error_analyzer(analyze);
		return ;
	}
	ft_lstaddback(&action.data, node);
	node = ft_stckpopnode(&analyze->stack);
	type = ((t_token *)node->data)->type;
	ft_lstdelone(&node, NULL);
	node = ft_stckpopnode(&analyze->stack);
	if (type == E_GREATAND)
		ft_lstadd(&action.data, node);
	else if (type == E_LESSAND)
		ft_lstadd(&action.data, node);
	ft_stckpush(&analyze->tree_node, &action, sizeof(t_action));
}

void			io_redirect_and_analyzer(t_analyze *analyze)
{
	analyze->state = P_IO_REDIRECT_AND;
	ft_stckpush(&analyze->stack, &analyze->token, sizeof(t_token));
	get_token(analyze);
}
