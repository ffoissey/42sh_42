/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_rpn.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 11:57:30 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		do_math(t_rpn_tk *first, t_rpn_tk *second, t_rpn_tk *curr)
{
	if (curr->value.type & (PRECEDENCE & AND))
		do_logical(first, second, curr);
	else if (curr->value.type & (PRECEDENCE & EQUAL))
		do_compare(first, second, curr);
	else if (curr->value.type & (PRECEDENCE & TIMES))
		do_high_op(first, second, curr);
	else if (curr->value.type & (PRECEDENCE & PLUS))
		do_low_op(first, second, curr);
}

static int8_t	check_forbidden_operation(t_rpn_tk *curr, t_rpn_tk *second)
{
	if (curr->value.type & (OPERATOR & DIVIDE)
			|| curr->value.type & (OPERATOR & MODULO))
	{
		if (second->value.digit == 0)
		{
			free(second);
			ft_dprintf(2, "42sh : Division by zero\n");
			return (FALSE);
		}
	}
	return (TRUE);
}

static int8_t	do_operation(t_rpn_tk *curr, t_stack *solve)
{
	t_rpn_tk	*second;
	t_list		*node;

	second = NULL;
	second = ft_stckpop(solve);
	node = ft_stckpopnode(solve);
	if (check_forbidden_operation(curr, second) == FALSE)
	{
		ft_lstdelone(&node, NULL);
		return (FAILURE);
	}
	do_math(node->data, second, curr);
	free(second);
	ft_stckpushnode(solve, node);
	return (SUCCESS);
}

static int8_t	handle_operator(t_rpn_tk *curr, t_stack *solve)
{
	t_list			*node;

	node = NULL;
	if (curr->value.type & (PRECEDENCE & UNARY_MINUS) && ft_stcksize(solve) > 0)
	{
		node = ft_stckpopnode(solve);
		do_unary(node->data, curr);
		ft_stckpushnode(solve, node);
	}
	else if (ft_stcksize(solve) < 2)
	{
		ft_dprintf(2, "Expression unsolvable\n");
		return (FAILURE);
	}
	else
	{
		if (do_operation(curr, solve) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

int8_t			calcul(t_stack *rpn, t_stack *solve)
{
	t_list		*node;
	t_rpn_tk	*curr;

	node = ft_stckpopnode(rpn);
	curr = node->data;
	if (curr->type == RPN_NUMBER)
		ft_stckpushnode(solve, node);
	else if (curr->type == RPN_OPERATOR)
	{
		if (handle_operator(curr, solve) == FAILURE)
		{
			ft_lstdelone(&node, NULL);
			return (FAILURE);
		}
		ft_lstdelone(&node, NULL);
	}
	return (SUCCESS);
}
