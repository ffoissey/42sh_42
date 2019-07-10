/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hmap_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 12:05:50 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/30 08:13:45 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "hashmap.h"
#include "ft_malloc.h"

static int		resize_check(t_hash *hashmap)
{
	size_t filled;

	filled = ft_hmap_filled(hashmap);
	if (filled < MIN_FILL && hashmap->map_size > MIN_MAP_SIZE << 1)
	{
		if (!ft_hmap_resize(hashmap, hashmap->map_size >> 1))
		{
			ft_dprintf(2, "SYSTEM FAILURE : Can't resize HMAP");
			return (0);
		}
	}
	return (1);
}

void			ft_del_hnode(void *node, void (*del)(void *))
{
	free(((t_hnode *)node)->key);
	((t_hnode *)node)->key = NULL;
	if (del)
		del(((t_hnode *)node)->data);
	((t_hnode *)node)->data = NULL;
	free(node);
}

static int		remove_first(t_hash *hashmap, uint32_t hash
								, t_hnode *data, void (*del)(void *))
{
	t_list	*tmp;

	tmp = hashmap->map[hash];
	hashmap->map[hash] = hashmap->map[hash]->next;
	ft_del_hnode(data, del);
	free(tmp);
	if (hashmap->used > 0)
		hashmap->used -= 1;
	if (!resize_check(hashmap))
		return (0);
	return (1);
}

static int		remove_data(t_hash *hashmap, t_list *ptr
								, t_hnode *data, void (*del)(void *))
{
	t_list *tmp;

	tmp = ptr->next->next;
	ft_del_hnode(data, del);
	free(ptr->next);
	ptr->next = tmp;
	if (hashmap->used > 0)
		hashmap->used -= 1;
	if (!resize_check(hashmap))
		return (0);
	return (1);
}

int				ft_hmap_remove(t_hash *hashmap, char *key, void (*del)(void *))
{
	t_list		*ptr;
	t_hnode		*data;

	if (!(ptr = hashmap->map[ft_hash_str(key, hashmap->map_size)]))
		return (0);
	data = ((t_hnode *)hashmap->map[ft_hash_str(key, hashmap->map_size)]->data);
	if (!ft_strcmp(data->key, key))
	{
		if (!remove_first(hashmap, ft_hash_str(key, hashmap->map_size)
															, data, del))
			return (0);
		return (1);
	}
	while (ptr->next != NULL)
	{
		data = ((t_hnode *)ptr->next->data);
		if (!ft_strcmp(data->key, key))
		{
			if (!remove_data(hashmap, ptr, data, del))
				return (0);
			return (1);
		}
		ptr = ptr->next;
	}
	return (0);
}
