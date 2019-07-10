/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vctreset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:37:53 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 10:37:54 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_vctreset(t_vector *vct)
{
	char *new;

	if (!(new = ft_strnew(VECTOR_BUFFER_SIZE)))
		return (1);
	ft_strdel(&(vct->buffer));
	vct->buffer = new;
	vct->size = VECTOR_BUFFER_SIZE;
	return (0);
}
