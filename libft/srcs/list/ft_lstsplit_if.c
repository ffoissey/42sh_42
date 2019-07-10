/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsplit_if.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 07:17:47 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/03 00:30:57 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*split(t_list *current, t_list **new, void *context, t_cmp cmp)
{
	t_list		*old;
	t_list		*tmp;

	old = NULL;
	while (current)
	{
		tmp = current;
		current = current->next;
		tmp->next = NULL;
		if (cmp(context, tmp->data))
			ft_lstaddback(new, tmp);
		else
			ft_lstaddback(&old, tmp);
	}
	return (old);
}

t_list			*ft_lstsplit_if(t_list **lst, void *context, t_cmp cmp)
{
	t_list		*new;
	t_list		*holder;

	if (!lst || !*lst || !cmp)
		return (NULL);
	new = NULL;
	while ((*lst) && cmp(context, (*lst)->data))
	{
		holder = (*lst);
		*lst = (*lst)->next;
		holder->next = NULL;
		ft_lstaddback(&new, holder);
	}
	if (*lst && (*lst)->next)
		(*lst)->next = split((*lst)->next, &new, context, cmp);
	return (new);
}
