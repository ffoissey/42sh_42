/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 13:34:46 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/17 14:41:17 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	if (!n)
		return (0);
	return (*((unsigned char *)s1) != *((unsigned char *)s2) || n == 1 ?
			*((unsigned char *)s1) - *((unsigned char *)s2) :
			ft_memcmp(++s1, ++s2, --n));
}
