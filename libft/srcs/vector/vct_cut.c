/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_cut.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:39:09 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 10:39:10 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/*
**	Deletes the first character of the specified vector,
**	And shifts the rest of the buffer one character to the left.
**	Always returns 0
*/

int8_t	vct_cut(t_vector *vector)
{
	shift_left(vector, 0);
	return (0);
}
