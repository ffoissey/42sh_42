/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hmap_insert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 12:07:05 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/07 02:35:18 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "hashmap.h"

static int		ft_create_hnode(t_list **alst, char *key, void *data)
{
	t_hnode		h_node;
	t_list		*newdir;

	if (key == NULL)
		return (0);
	ft_bzero(&h_node, sizeof(t_hnode));
	h_node.hits = 0;
	h_node.key = ft_strdup(key);
	h_node.data = data;
	if (h_node.key == NULL || h_node.data == NULL)
		return (0);
	if (!(newdir = ft_lstnew(&h_node, sizeof(t_hnode))))
		return (0);
	ft_lstadd(alst, newdir);
	return (1);
}

int				ft_hmap_insert(t_hash *hashmap, char *key, void *data)
{
	size_t		key_len;
	uint32_t	hash;

	if (ft_hmap_getdata(hashmap, key))
		return (0);
	if (ft_hmap_filled(hashmap) > MAX_FILL)
	{
		if (!ft_hmap_resize(hashmap, hashmap->map_size << 1))
		{
			ft_dprintf(2, "SYSTEM FAILURE : Can't resize HMAP");
			return (-1);
		}
	}
	hash = ft_hash_str(key, hashmap->map_size);
	if (!ft_create_hnode(&hashmap->map[hash], key, data))
		return (0);
	hashmap->used += 1;
	if ((key_len = ft_strlen(key)) > hashmap->print_pad)
		hashmap->print_pad = key_len;
	return (1);
}
