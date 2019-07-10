/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hmap_resize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 13:18:15 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/30 08:14:07 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "hashmap.h"
#include "ft_malloc.h"

size_t		ft_get_two_pw(size_t nb)
{
	size_t i;

	i = 0;
	while (nb != 1)
	{
		nb >>= 1;
		i++;
	}
	return (i);
}

size_t		ft_hmap_filled(t_hash *hashmap)
{
	return ((hashmap->used << POW_128) >> ft_get_two_pw(hashmap->map_size));
}

size_t		ft_hmap_filled_norm(t_hash *hashmap)
{
	return ((ft_hmap_filled(hashmap) * 100) >> POW_128);
}

static void	relocate_hash(t_hash *hashmap, t_list **new, size_t nw_size)
{
	size_t	i;
	t_list	*ptr;
	t_list	*tmp;
	t_hnode	*node;

	i = 0;
	while (i < hashmap->map_size)
	{
		ptr = hashmap->map[i];
		if (ptr)
		{
			while (ptr != NULL)
			{
				tmp = ptr->next;
				ptr->next = NULL;
				node = (t_hnode *)ptr->data;
				ft_lstadd(&(new[ft_hash_str(node->key, nw_size)]), ptr);
				ptr = tmp;
			}
		}
		i++;
	}
}

int			ft_hmap_resize(t_hash *hashmap, size_t nw_size)
{
	t_list		**new;

	new = ft_memalloc(nw_size * sizeof(t_list *));
	if (!new)
		return (0);
	relocate_hash(hashmap, new, nw_size);
	free(hashmap->map);
	hashmap->map = new;
	hashmap->map_size = nw_size;
	return (1);
}
