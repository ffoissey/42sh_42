/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 10:49:57 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/15 15:48:18 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

#include "libft.h"

int		ft_lstaddback(t_list **alst, t_list *new)
{
	t_list	*holder;

	if (!new)
		return (-1);
	holder = *alst == NULL ? NULL : *alst;
	if (holder)
	{
		while (holder->next != NULL)
			holder = holder->next;
		holder->next = new;
		return (1);
	}
	*alst = new;
	return (1);
}
