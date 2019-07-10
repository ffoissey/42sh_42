/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hmap_hits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 16:46:55 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/04 17:03:36 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "hashmap.h"
#define NOT_FOUND	-2
#define MAX_HIT		-3

int8_t		ft_hmap_hits(t_hash *hashmap, char *key)
{
	uint32_t	hash;
	t_list		*ptr;
	t_hnode		*node;

	hash = ft_hash_str(key, hashmap->map_size);
	if (!(ptr = hashmap->map[hash]))
		return (FAILURE);
	while (ptr != NULL)
	{
		node = ((t_hnode *)ptr->data);
		if (!ft_strcmp(node->key, key))
		{
			if (node->hits >= UINT32_MAX)
				return (MAX_HIT);
			node->hits += 1;
			return (SUCCESS);
		}
		ptr = ptr->next;
	}
	return (NOT_FOUND);
}
