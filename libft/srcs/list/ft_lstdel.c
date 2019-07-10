/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 12:56:27 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/07 05:40:37 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static t_list	*eraser(t_list *current, void (*del)(void *))
{
	if (current)
	{
		eraser(current->next, del);
		ft_lstdelone(&current, del);
	}
	return (NULL);
}

void			*ft_lstdel(t_list **alst, void (*del)(void *))
{
	if (!alst || !*alst)
		return (NULL);
	*alst = eraser(*alst, del);
	return (NULL);
}
