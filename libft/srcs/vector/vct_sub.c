/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:43:26 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 10:43:27 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

char	*vct_sub(t_vector *vector, uint64_t start, uint64_t len)
{
	return (ft_strsub(vector->buffer, start, len));
}
