/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vctrescale.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:36:56 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 10:37:02 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_vctrescale(t_vector *vector)
{
	char	*new;

	if (!(new = ft_strnew(vector->size + VECTOR_BUFFER_SIZE)))
		return (1);
	vector->size += VECTOR_BUFFER_SIZE;
	ft_strcpy(new, vector->buffer);
	ft_strdel(&(vector->buffer));
	vector->buffer = new;
	return (0);
}
