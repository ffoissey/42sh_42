/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_yard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 14:38:19 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int8_t	close_bracket(t_stack *operator, t_stack *rpn)
{
	t_list		*node;

	while (is_left_p(operator) == FALSE)
		if (ft_stckpushnode(rpn, ft_stckpopnode(operator)) == FAILURE)
			return (FAILURE);
	if (is_left_p(operator) == TRUE)
	{
		node = ft_stckpopnode(operator);
		ft_lstdelone(&node, NULL);
	}
	return (SUCCESS);
}

static int8_t	handle_operator(t_list *curr, t_stack *operator, t_stack *rpn)
{
	t_rpn_tk *token;

	token = curr->data;
	while (need_pop_operator(token, operator) == TRUE)
		if (ft_stckpushnode(rpn, ft_stckpopnode(operator)) == FAILURE)
			return (FAILURE);
	if (ft_stckpushnode(operator, curr) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int8_t	handle_bracket(t_list *curr, t_stack *operator, t_stack *rpn)
{
	t_rpn_tk	*token;

	token = curr->data;
	if (token->value.type == OPEN_P)
	{
		if (ft_stckpushnode(operator, curr) == FAILURE)
			return (FAILURE);
	}
	else if (close_bracket(operator, rpn) == FAILURE)
		return (FAILURE);
	if (token->value.type == CLOSE_P)
		ft_lstdelone(&curr, NULL);
	return (SUCCESS);
}

static int8_t	handle_infix_token(t_list *current
				, t_stack *rpn, t_stack *operator)
{
	t_rpn_tk	*token;

	token = current->data;
	if (token->type == RPN_NUMBER)
	{
		if (ft_stckpushnode(rpn, current) == FAILURE)
			return (FAILURE);
	}
	else if (token->type == RPN_OPERATOR)
	{
		if (handle_operator(current, operator, rpn) == FAILURE)
			return (FAILURE);
	}
	else if (token->type == RPN_PARENT_OPEN || token->type == RPN_PARENT_CLOSE)
	{
		if (handle_bracket(current, operator, rpn) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

int8_t			ft_shunting_yds(t_stack *infix, t_stack *rpn)
{
	t_list		*node;
	t_stack		operator;

	ft_stckinit(&operator);
	while (ft_stcksize(infix) > 0)
	{
		node = ft_stckpopnode(infix);
		if (handle_infix_token(node, rpn, &operator) == FAILURE)
			return (FAILURE);
	}
	while (ft_stcksize(&operator) > 0)
	{
		node = ft_stckpopnode(&operator);
		if (ft_stckpushnode(rpn, node) == FAILURE)
			return (FAILURE);
	}
	ft_stckdestroy(&operator, NULL);
	return (SUCCESS);
}
