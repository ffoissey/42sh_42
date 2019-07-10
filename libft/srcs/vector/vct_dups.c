/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_dups.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:40:33 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 10:40:35 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/*
**	Allocate a new vector and set the internal buffer to a copy of the
** 	specified string.
**	Returns a pointer on success or NULL on malloc error.
*/

t_vector	*vct_dups(char *str)
{
	t_vector	*new;
	uint64_t	len;

	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	if ((new = vct_new(len)) == NULL)
		return (NULL);
	vct_scpy(new, str, len);
	return (new);
}
