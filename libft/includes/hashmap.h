/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 15:07:32 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/04 17:03:27 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHMAP_H
# define HASHMAP_H

# include <stdlib.h>
# include "list.h"
# define MIN_MAP_SIZE 8
# define MIN_FILL 26
# define MAX_FILL 89
# define POW_128 7
# define SUCCESS 0
# define FAILURE -1

typedef struct	s_hash
{
	size_t		print_pad;
	size_t		map_size;
	size_t		used;
	t_list		**map;
}				t_hash;

typedef struct	s_hnode
{
	uint32_t	hits;
	char		*key;
	void		*data;
}				t_hnode;

uint32_t		ft_hash_str(char *key, size_t tab_size);
t_hash			ft_hmap_init(size_t size);
void			ft_print_hashmap(t_hash *hashmap);
void			ft_print_hashmap_p(t_hash *hashmap);
void			ft_simplified_hash_print(t_hash *hashmap);
void			*ft_hmap_getdata(t_hash *hashmap, char *key);
int				ft_hmap_remove(t_hash *hashmap, char *key, void (*del)(void *));
int				ft_hmap_insert(t_hash *hashmap, char *key, void *data);
size_t			ft_hmap_filled(t_hash *hashmap);
size_t			ft_hmap_filled_norm(t_hash *hashmap);
size_t			ft_get_two_pw(size_t nb);
int				ft_hmap_resize(t_hash *hashmap, size_t nw_size);
void			ft_hmap_free_content(t_hash *hashmap, void (*del)(void *));
void			ft_del_hnode(void *node, void (*del)(void *));
size_t			ft_hmap_collision(t_hash *hashmap);
size_t			ft_hmap_collision_rate(t_hash *hashmap);
int8_t			ft_hmap_hits(t_hash *hashmap, char *key);

#endif
