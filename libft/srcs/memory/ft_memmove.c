/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 11:55:32 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/17 14:41:17 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	if (n)
	{
		if ((unsigned long)dst < (unsigned long)src)
			return (ft_memcpy(dst, src, n));
		else
		{
			while (--n > 0)
				((unsigned char *)dst)[n] = ((unsigned char *)src)[n];
			*(unsigned char *)dst = *(unsigned char *)src;
		}
	}
	return (dst);
}
