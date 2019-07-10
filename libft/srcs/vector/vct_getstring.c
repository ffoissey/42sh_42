/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_getstring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:40:05 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 10:40:14 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/*
** Returns the pointer to the actual internal buffer of the specified vector.
*/

char	*vct_get_string(t_vector *vector)
{
	return (vector->buffer);
}
