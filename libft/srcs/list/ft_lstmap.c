/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 14:04:04 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/11 15:57:37 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		mapper(t_list *lst, t_list **map, void *context, t_lstmap func)
{
	t_list	*node;

	node = NULL;
	if (!lst)
		return (0);
	if ((node = func(context, lst->data)) == NULL)
		return (-1);
	ft_lstaddback(map, node);
	return (mapper(lst->next, map, context, func));
}

t_list	*ft_lstmap(t_list *lst, void *context, t_lstmap func, t_del del)
{
	t_list	*map;

	if (func == NULL)
		return (NULL);
	map = NULL;
	if (mapper(lst, &map, context, func))
	{
		ft_lstdel(&map, del);
		return (NULL);
	}
	return (map);
}
