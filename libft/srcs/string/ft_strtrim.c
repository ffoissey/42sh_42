/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:10:39 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/30 08:11:19 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>
#include "ft_malloc.h"

static char			*ft_chr(const char *s, int c)
{
	if (!*s)
		return (*s == (char)c ? (char *)s : NULL);
	return (*s == (char)c ? (char *)s : ft_strchr(++s, c));
}

static char			*ft_ncpy(char *dst, const char *src, size_t len)
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

static char			*ft_sub(char const *s, unsigned int start, size_t len)
{
	char			*sub;

	if (!(sub = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	sub = ft_ncpy(sub, s + start, len);
	sub[len] = '\0';
	return (sub);
}

static char const	*trimmer(char const *s, int *len)
{
	size_t		i;
	size_t		s_len;
	char const	*str;

	i = 0;
	s_len = 0;
	while (ft_chr("\n\t ", s[i]) && s[i])
		i++;
	if (*s)
		while (s[++s_len])
			;
	if (i == s_len)
		return (NULL);
	str = s + i;
	while (s[i])
	{
		*len += 1;
		i++;
	}
	while (ft_chr("\n\t ", s[--i]))
		*len -= 1;
	return (str);
}

char				*ft_strtrim(char const *s)
{
	int			len;
	char		*trim;
	char const	*str;

	if (!s)
		return (NULL);
	len = 0;
	str = trimmer(s, &len);
	if (str == NULL)
	{
		if (!(trim = (char *)malloc(sizeof(char) * 1)))
			return (NULL);
		*trim = '\0';
		return (trim);
	}
	if (!(trim = ft_sub(str, 0, len)))
		return (NULL);
	return (trim);
}
