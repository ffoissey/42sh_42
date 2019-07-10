/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 16:07:03 by nrechati          #+#    #+#             */
/*   Updated: 2019/01/17 14:41:17 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strrev(char *str)
{
	int a;
	int b;

	b = 0;
	if (!str)
		return (NULL);
	while (str[b])
	{
		b++;
	}
	b--;
	a = 0;
	while (a < b)
	{
		str[a] ^= str[b];
		str[b] ^= str[a];
		str[a] ^= str[b];
		a++;
		b--;
	}
	return (str);
}
