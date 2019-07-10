/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:15:26 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int8_t	only_whitespaces_after(const char *str, const uint32_t index,
					const char direction)
{
	uint32_t idx;

	idx = index;
	if (direction > 0)
	{
		while (str[idx] != '\0' && str[idx] != ' ')
			++idx;
		while (str[idx] != '\0')
			if (str[idx++] != ' ')
				return (FALSE);
	}
	else
	{
		while (idx > 0 && str[idx] != ' ')
			--idx;
		while (idx > 0)
			if (str[idx--] != ' ')
				return (FALSE);
	}
	return (idx == 0 || str[idx] == '\0' || str[idx] == ' ' ? FALSE : TRUE);
}

uint32_t		get_next_char(const char *str, uint32_t index,
					const char direction)
{
	if (only_whitespaces_after(str, index, direction) == TRUE)
		return (index);
	if (direction > 0)
	{
		while (str[index] != '\0' && str[index] != ' ')
			++index;
		while (str[index] == ' ')
			++index;
	}
	else
	{
		while (index > 0 && str[index - 1] != ' ')
			--index;
		while (index > 0 && str[index - 1] == ' ')
			--index;
	}
	return (index);
}
