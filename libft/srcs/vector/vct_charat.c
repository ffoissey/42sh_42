/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_charat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:38:58 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 10:38:59 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/*
**	Returns the character at the index `index` of the specified vector.
**	Or 0 if index is bigger than the buffer length.
*/

char	vct_charat(t_vector *vct, uint64_t index)
{
	return (vct->buffer[index]);
}
