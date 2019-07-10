/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:51:04 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/30 06:21:28 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>
#include "ft_malloc.h"

static void	ft_init(void *s, size_t n)
{
	if (!n)
		return ;
	*((char *)s) = 0;
	while (--n > 0)
		((char *)s)[n] = '\0';
}

char		*ft_strnew(size_t size)
{
	char	*str;

	if (!(str = (char *)malloc(size + 1)))
		return (NULL);
	ft_init(str, size + 1);
	return (str);
}
