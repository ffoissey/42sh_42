/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_getcopy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:39:55 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 10:39:56 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/*
** Returns an allocated copy of the internal buffer of the specified vector.
** or NULL on error.
*/

char	*vct_getcopy(t_vector *vector)
{
	return (ft_strsub(vector->buffer, 0, vct_len(vector)));
}
