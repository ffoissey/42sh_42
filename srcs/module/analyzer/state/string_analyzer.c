/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 21:17:49 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	flush_string(t_analyze *analyze)
{
	t_list		*node;
	t_action	action;

	node = NULL;
	analyze->state = P_STRING_FLUSH;
	ft_bzero(&action, sizeof(t_action));
	action.type = A_ARGS;
	analyze->valid = 1;
	while (ft_stcksize(&analyze->stack) != 0)
	{
		node = ft_stckpopnode(&analyze->stack);
		ft_lstadd(&action.data, node);
	}
	ft_stckpush(&analyze->tree_node, &action, sizeof(t_action));
	return ;
}

void	string_analyzer(t_analyze *analyze)
{
	analyze->state = P_STRING;
	ft_stckpush(&analyze->stack, &analyze->token, sizeof(t_token));
	get_token(analyze);
}
