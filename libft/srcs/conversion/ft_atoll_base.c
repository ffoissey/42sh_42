/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 20:47:23 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/07 05:28:03 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long long	ft_base_check_and_strlen(char *base)
{
	long long		i;
	long long		length;

	length = 0;
	while (base[length] != '\0')
	{
		if (base[length] == '+' || base[length] == '-')
			return (0);
		i = length - 1;
		while (i >= 0)
		{
			if (base[i] == base[length])
				return (0);
			i--;
		}
		length++;
	}
	return (length);
}

static long long	ft_is_in_base(char *str, char c)
{
	long long	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

long long			ft_atoll_base(char *str, char *base)
{
	long long	i;
	long long	sig;
	long long	nbase;
	long long	value;

	i = 0;
	sig = 1;
	value = 0;
	nbase = ft_base_check_and_strlen(base);
	if (nbase <= 1)
		return (0);
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '+' || str[i] == '-')
		sig *= (str[i++] == '-' ? -1 : 1);
	while (ft_is_in_base(base, str[i]) != -1)
	{
		value = value * nbase + ft_is_in_base(base, str[i]);
		i++;
	}
	if (!str[i] || str[i] == '-' || str[i] == '+')
		return (sig * value);
	else
		return (0);
}
