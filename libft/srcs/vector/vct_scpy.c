/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_scpy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:44:11 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 10:44:12 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/*
**	Copies `len` characters from the `source` string to the `dest` vector.
*/

int8_t	vct_scpy(t_vector *dest, char *source,
			uint64_t len)
{
	if (dest->size < len)
		vct_resize(dest, len + 1);
	ft_strncpy(dest->buffer, source, len);
	return (0);
}
