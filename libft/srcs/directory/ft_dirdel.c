/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dirdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 07:25:43 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/15 16:03:59 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	dir_del(void *file)
{
	t_status	*tmp;

	tmp = (t_status *)file;
	if (tmp->path)
		ft_strdel(&tmp->path);
	if (tmp->name)
		ft_strdel(&tmp->name);
}

void		ft_dirdel(t_list **dirlist)
{
	ft_lstdel(dirlist, dir_del);
}
