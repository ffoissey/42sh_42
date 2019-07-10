/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:39:19 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 10:39:20 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/*
**	Deletes a vector and its internal buffer
*/

void		vct_del(t_vector **vector)
{
	if (vector == NULL || *vector == NULL)
		return ;
	ft_strdel(&(*vector)->buffer);
	free(*vector);
	*vector = NULL;
}
