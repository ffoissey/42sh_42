/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_scale.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:43:52 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 10:43:53 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

int8_t	vct_scale(t_vector *vector)
{
	char *new;

	if ((new = ft_strnew(vector->size + vector->scale)) == NULL)
		return (-1);
	vector->size += vector->scale;
	ft_strncpy(new, vector->buffer, vct_len(vector));
	ft_strdel(&vector->buffer);
	vector->buffer = new;
	return (0);
}
