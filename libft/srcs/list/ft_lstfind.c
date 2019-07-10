/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 11:09:07 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/21 20:06:04 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_list	*ft_lstfind(t_list *lst, void *to_find, int (*f)(void *, void *))
{
	if (lst == NULL)
		return (NULL);
	return (f(lst->data, to_find) ? lst : ft_lstfind(lst->next, to_find, f));
}
