/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stckpushnode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 14:00:42 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/25 14:05:40 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_stckpushnode(t_stack *stack, t_list *node)
{
	if (!stack || !node)
		return (-1);
	node->next = stack->head;
	stack->head = node;
	stack->size += 1;
	return (0);
}
