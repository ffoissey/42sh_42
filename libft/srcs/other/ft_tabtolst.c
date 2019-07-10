/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabtolst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 01:01:22 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/17 14:41:17 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_list	*ft_tabtolst(char **tab)
{
	t_list	*lst;
	t_list	*tmp;
	int		i;

	lst = NULL;
	i = 0;
	while (tab[i])
		i++;
	while (--i >= 0)
	{
		if (!(tmp = ft_lstnew(tab[i], ft_strlen(tab[i]) + 1)))
			return (ft_lstdel(&lst, NULL));
		ft_lstadd(&lst, tmp);
	}
	return (lst);
}
