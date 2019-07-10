/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_pop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:45:04 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 10:45:04 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/*
**	Deletes the last character of the specified vector.
*/

int8_t	vct_pop(t_vector *vector)
{
	if (vct_len(vector) == 0)
		return (0);
	vector->buffer[vct_len(vector) - 1] = '\0';
	return (0);
}
