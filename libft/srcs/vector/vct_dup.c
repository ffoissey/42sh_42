/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:39:41 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 10:39:42 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/*
**	Duplicates a vector and returns a pointer to the freshly allocated
**	structure.
*/

t_vector	*vct_dup(t_vector *vect)
{
	return (vct_dups(vct_get_string(vect)));
}
