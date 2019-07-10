/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove_if.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 07:17:47 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/03 00:31:28 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	return_manager(int mask)
{
	static int	check = 0;
	int			holder;

	if (mask == 1)
		return (check = 1);
	else if (mask == 0)
	{
		holder = check;
		check = 0;
		return (holder);
	}
	return (check);
}

t_list		*ereaser(t_list *current, void *data, t_cmp cmp, t_del del)
{
	t_list		*tmp;

	if (!current)
		return (NULL);
	else if (cmp(current->data, data))
	{
		tmp = current->next;
		ft_lstdelone(&current, del);
		tmp = ereaser(tmp, data, cmp, del);
		return_manager(1);
		return (tmp);
	}
	else
	{
		current->next = ereaser(current->next, data, cmp, del);
		return (current);
	}
}

int			ft_lstremove_if(t_list **lst, void *data, t_cmp cmp, t_del del)
{
	t_list		*tmp;

	if (!lst || !*lst || !cmp)
		return (return_manager(0));
	if (cmp((*lst)->data, data))
	{
		tmp = (*lst)->next;
		ft_lstdelone(lst, del);
		*lst = tmp;
		return_manager(1);
		return (ft_lstremove_if(lst, data, cmp, del));
	}
	if ((*lst)->next)
		(*lst)->next = ereaser((*lst)->next, data, cmp, del);
	return (return_manager(0));
}
