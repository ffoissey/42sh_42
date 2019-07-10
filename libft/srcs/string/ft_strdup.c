/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 16:45:20 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/30 06:17:20 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>
#include "ft_malloc.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;

	if (!s1)
		return (NULL);
	if (!(dst = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1)))
		return (NULL);
	return (ft_strcpy(dst, s1));
}
