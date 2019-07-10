/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:42:17 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 10:42:18 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/*
** Return then length of the vector
** Equivalent to strlen(vector->buffer)
*/

uint64_t			vct_len(t_vector *vector)
{
	return (ft_strlen(vct_get_string(vector)));
}
