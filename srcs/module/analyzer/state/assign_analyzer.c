/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 00:37:52 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	assign_flush_analyzer(t_analyze *analyze)
{
	t_list		*node;
	t_action	action;

	analyze->state = P_ASSIGN_FLUSH;
	ft_bzero(&action, sizeof(t_action));
	node = ft_stckpopnode(&analyze->stack);
	ft_lstadd(&action.data, node);
	node = ft_stckpopnode(&analyze->stack);
	ft_lstadd(&action.data, node);
	action.type = A_ASSIGN;
	ft_stckpush(&analyze->tree_node, &action, sizeof(t_action));
	analyze->valid = 1;
}

void	assign_data_analyzer(t_analyze *analyze)
{
	analyze->state = P_ASSIGN_DATA;
	ft_stckpush(&analyze->stack, &analyze->token, sizeof(t_token));
	get_token(analyze);
}

void	assign_name_analyzer(t_analyze *analyze)
{
	if (ft_isdigit(*analyze->token.data))
		analyze->state = P_STRING;
	else
		analyze->state = P_ASSIGN_NAME;
	ft_stckpush(&analyze->stack, &analyze->token, sizeof(t_token));
	get_token(analyze);
}
