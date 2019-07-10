/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_ctx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 10:59:10 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/02 17:12:00 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstiter_ctx(t_list *lst, void *context
				, int (*f)(void *context, void *data))
{
	if (lst)
	{
		if (f(context, lst->data) == FAILURE)
			return (FAILURE);
		return (ft_lstiter_ctx(lst->next, context, f));
	}
	return (SUCCESS);
}
