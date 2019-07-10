/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:55:52 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/30 06:24:18 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>
#include "ft_malloc.h"

static char	*ft_ncpy(char *dst, const char *src, size_t len)
{
	char	*d;

	d = dst;
	if (!len)
		return (dst);
	while (*src && len)
	{
		*d++ = *src++;
		len--;
	}
	while (len)
	{
		*d++ = '\0';
		len--;
	}
	return (dst);
}

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*sub;

	if (!s)
		return (NULL);
	if (!(sub = (char *)malloc(len + 1)))
		return (NULL);
	sub = ft_ncpy(sub, s + start, len);
	sub[len] = '\0';
	return (sub);
}
