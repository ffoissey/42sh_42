/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_taboneach.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 16:15:54 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/03 00:37:23 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_taboneach(char **current, void *context
							, char *(*mod)(char *, void *))
{
	char		*holder;

	if (current == NULL)
		return (0);
	holder = mod(*current, context);
	ft_strdel(current);
	*current = holder;
	return (ft_taboneach(current, context, mod));
}
