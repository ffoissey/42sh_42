/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stckdestroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 21:26:01 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/18 00:35:00 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_stckdestroy(t_stack *stack, void (*f)(void *))
{
	ft_lstdel(&stack->head, f);
	stack->size = 0;
}
