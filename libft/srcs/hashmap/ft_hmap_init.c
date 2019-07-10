/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hmap_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 12:01:39 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/03 17:00:20 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "hashmap.h"

t_hash	ft_hmap_init(size_t size)
{
	t_hash data;

	data.print_pad = 0;
	data.used = 0;
	data.map_size = size;
	data.map = ft_memalloc(data.map_size * sizeof(t_list *));
	return (data);
}
