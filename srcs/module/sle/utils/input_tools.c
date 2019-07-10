/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:15:09 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int					ft_putc(const int c)
{
	write(2, &c, 1);
	return (42);
}

uint8_t				is_eof(const char *buffer)
{
	if (buffer[0] == 4)
		return (TRUE);
	return (FALSE);
}

inline uint8_t		is_separator(char character[READ_SIZE + 1])
{
	if (character[0] == IFS_CHAR)
		return (TRUE);
	return (FALSE);
}

inline uint8_t		is_printable(char c[READ_SIZE])
{
	if (ft_isprint(c[0]) && ft_strchr(c, '\n') == NULL)
		return (TRUE);
	return (FALSE);
}

uint64_t			compute_mask(char c[READ_SIZE])
{
	uint16_t	shift;
	uint16_t	index;
	uint64_t	value;
	uint64_t	tmp;

	shift = 56;
	index = 0;
	value = 0;
	while (index < 8 && c[index] != '\0')
	{
		tmp = c[index++];
		tmp <<= shift;
		value |= tmp;
		shift -= 8;
	}
	return (value);
}
