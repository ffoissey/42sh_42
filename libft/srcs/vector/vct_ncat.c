/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_ncat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:45:39 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 10:45:40 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/*
**	Concatenates `len` characters from the source vector to the dest vector.
**	Resizes automatically.
*/

int8_t		vct_ncat(t_vector *dest, t_vector *source,
						uint64_t len)
{
	vct_scat(dest, source->buffer, len);
	return (0);
}
