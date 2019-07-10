/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 12:37:47 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 10:37:38 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int64_t	bit64_location(const char *cp, const char *str, uint8_t is64bit)
{
	if (cp[0] == 0)
		return (cp - str);
	if (cp[1] == 0)
		return (cp - str + 1);
	if (cp[2] == 0)
		return (cp - str + 2);
	if (cp[3] == 0)
		return (cp - str + 3);
	if (is64bit)
	{
		if (cp[4] == 0)
			return (cp - str + 4);
		if (cp[5] == 0)
			return (cp - str + 5);
		if (cp[6] == 0)
			return (cp - str + 6);
		if (cp[7] == 0)
			return (cp - str + 7);
	}
	return (-1);
}

static uint64_t	locate_eol(t_magic *magic, const unsigned long int *lw_ptr
							, const char *str)
{
	int64_t		length;
	const char	*cp;

	cp = NULL;
	while (1)
	{
		magic->lw = *lw_ptr++;
		if (((magic->lw - magic->lo) & ~magic->lw & magic->hi) != 0)
		{
			cp = (const char *)(lw_ptr - 1);
			length = bit64_location(cp, str, (sizeof(magic->lw) > 4) ? 1 : 0);
			if (length != -1)
				return (length);
		}
	}
	return (0);
}

static void		prepare_masks(t_magic *magic)
{
	magic->hi = 0x80808080;
	magic->lo = 0x01010101;
	if (sizeof(magic->lw) > 4)
	{
		magic->hi = ((magic->hi << 16) << 16) | magic->hi;
		magic->lo = ((magic->lo << 16) << 16) | magic->lo;
	}
}

size_t			ft_strlen(const char *str)
{
	t_magic						magic;
	const char					*char_ptr;
	const unsigned long int		*longword_ptr;

	if (str == NULL || *str == '\0')
		return (0);
	ft_bzero(&magic, sizeof(t_magic));
	longword_ptr = NULL;
	magic.lw = 0;
	char_ptr = str;
	while (((unsigned long int)char_ptr & (sizeof(magic.lw) - 1)) != 0)
	{
		++char_ptr;
		if (*char_ptr == '\0')
			return (char_ptr - str);
	}
	prepare_masks(&magic);
	longword_ptr = (unsigned long int *)char_ptr;
	return (locate_eol(&magic, longword_ptr, char_ptr) + char_ptr - str);
}
