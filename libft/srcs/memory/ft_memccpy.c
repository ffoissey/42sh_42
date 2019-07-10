/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 17:11:50 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/17 14:41:17 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	if (!n)
		return (NULL);
	*(unsigned char *)dst = *(unsigned char *)src;
	if (*(unsigned char *)src == (unsigned char)c)
		return ((unsigned char *)dst + 1);
	return (n == 1 ? NULL : ft_memccpy(++dst, ++src, c, --n));
}
