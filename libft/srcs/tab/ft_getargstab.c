/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getargstab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 20:38:08 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/25 18:28:14 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	**ft_getargstab(int ac, char **av)
{
	char	**tab;
	int		i;
	int		j;

	i = 1;
	j = 0;
	tab = NULL;
	while (i < ac && av[i][0] == '-')
		i++;
	if (i < ac)
	{
		tab = ft_memalloc((sizeof(char *) * (ac - i + 1)));
		while (i < ac)
			tab[j++] = av[i++];
		tab[j] = NULL;
	}
	return (tab);
}
