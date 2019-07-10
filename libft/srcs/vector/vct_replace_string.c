/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_replace_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:44:02 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 10:44:03 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/*
**	Replaces the characters from `start_index` to `end_index` inclusively,
**	with the specified string `str`.
**	Returns -1 on invalid start/end indexes or 0 on success.
*/

static void	do_diff(uint64_t tmp, t_vector *vector, uint64_t start_index,
				char *str)
{
	shift_nleft(vector, start_index, tmp);
	while (*str != '\0')
		vector->buffer[start_index++] = *str++;
}

int8_t		vct_replace_string(t_vector *vector,
					uint64_t start_index, uint64_t end_index, char *str)
{
	uint64_t	del_diff;
	uint64_t	str_len;
	uint64_t	tmp;

	if (start_index > vct_len(vector) || start_index >= end_index)
		return (-1);
	str_len = ft_strlen(str);
	del_diff = end_index - start_index;
	if (str_len > del_diff)
	{
		vct_resize(vector, vct_len(vector) + (str_len - del_diff) + 2);
		tmp = str_len - del_diff;
		shift_nright(vector, end_index, tmp);
		while (*str != '\0')
			vector->buffer[start_index++] = *str++;
	}
	else if (str_len < del_diff)
		do_diff(del_diff - str_len, vector, start_index, str);
	else
		while (*str != '\0')
			vector->buffer[start_index++] = *str++;
	return (0);
}
