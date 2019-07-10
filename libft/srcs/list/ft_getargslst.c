/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getargslst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 17:43:50 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/02 13:56:08 by cedricmpa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_getargslst(int ac, char **av)
{
	t_list	*lst;
	int		i;

	i = 1;
	lst = NULL;
	while (i < ac && av[i][0] == '-' && av[i][1] && av[i][1] != '-')
		i++;
	if (i < ac && av[i][0] == '-' && av[i][1] == '-' && !av[i][2])
		i++;
	if (i < ac)
	{
		while (i < ac)
		{
			ft_lstadd(&lst, ft_lstnew(av[i], ft_strlen(av[i]) + 1));
			i++;
		}
	}
	return (lst);
}
