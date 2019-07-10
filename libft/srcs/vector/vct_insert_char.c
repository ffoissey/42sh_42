/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_insert_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:40:21 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 10:40:23 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "libft.h"

/*
** Inserts the single character `c`  into the specified vector,
** at the index `index`.
** Return 0 on succes or -1 if the index
** is bigger than the length of the vector.
*/

int8_t	vct_insert_char(t_vector *vector, char c, uint64_t index)
{
	uint64_t	v_len;

	v_len = vct_len(vector);
	if (index > v_len)
		return (-1);
	if (v_len + 1 >= vector->size)
		vct_scale(vector);
	shift_right(vector, index);
	vector->buffer[index] = c;
	return (0);
}
