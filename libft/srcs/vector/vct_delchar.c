/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_delchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:39:26 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 10:39:28 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

int8_t	vct_del_char(t_vector *vector, uint64_t index)
{
	if (index > vct_len(vector))
		return (-1);
	shift_left(vector, index);
	return (0);
}
