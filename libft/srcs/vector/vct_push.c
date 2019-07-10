/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:44:36 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 10:44:37 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/*
**	Adds the character `c` to the beginning of the vector(at the index 0).
**	Return 0 on success or -1 on allocation error.
**
**	As with all vector functions, if the LENGTH of the new buffer is bigger
**	than the buffers SIZE, an equivalent reallocation occurs.
*/

int8_t	vct_push(t_vector *vector, char c)
{
	if (vct_len(vector) + 1 >= vector->size)
		if (vct_scale(vector) == -1)
			return (-1);
	shift_right(vector, 0);
	vector->buffer[0] = c;
	return (0);
}
