/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_del_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:39:34 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 10:39:35 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/*
**	Deletes a one or more character in the specified vector.
**	Starting from index start to start+len.
**	It also shifts the rest of the buffer accordingly.
**	Always returns 0.
*/

int8_t	vct_del_string(t_vector *vector,
					uint64_t start, uint64_t len)
{
	shift_nleft(vector, start, len);
	return (0);
}
