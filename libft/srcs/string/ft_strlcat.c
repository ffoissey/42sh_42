/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 17:26:00 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/17 14:41:17 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	int					i;
	int					j;
	int					len;
	unsigned int		n;

	n = size;
	i = 0;
	j = 0;
	len = ft_strlen(dest) + ft_strlen(src);
	while (n-- != 0 && dest[i] != '\0')
		i++;
	n = size - i;
	if (!n)
		return (size + ft_strlen(src));
	while (src[j] && n > 0)
	{
		if (n > 1)
			dest[i++] = src[j++];
		n--;
	}
	dest[i] = '\0';
	return (len);
}
