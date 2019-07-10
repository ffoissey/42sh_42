/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 15:05:01 by nrechati          #+#    #+#             */
/*   Updated: 2019/05/29 18:41:26 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "hashmap.h"

static uint32_t	ft_norm_hash(uint32_t hash, size_t tab_size)
{
	uint32_t n_hash;

	n_hash = hash & (tab_size - 1);
	return (n_hash);
}

uint32_t		ft_hash_str(char *key, size_t tab_size)
{
	uint32_t hash;
	uint32_t i;

	i = 0;
	hash = i;
	while (key[i])
	{
		hash += key[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
		i++;
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	hash = ft_norm_hash(hash, tab_size);
	return (hash);
}
