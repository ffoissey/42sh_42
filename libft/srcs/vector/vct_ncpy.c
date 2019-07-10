/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_ncpy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:45:32 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 10:45:33 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/*
**	Copies `len` character from the `source` vector to the `dest` vector.
**	Resizes accordingly.
*/

int8_t	vct_ncpy(t_vector *dest, t_vector *source,
						uint64_t len)
{
	vct_scpy(dest, source->buffer, len);
	return (0);
}
