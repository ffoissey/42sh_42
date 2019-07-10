/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 20:52:12 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 07:50:41 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	converter(const char *str, long result, int sign)
{
	if (!ft_isdigit(*str))
		return (sign == 1 ? result : -result);
	result = result * 10 + *str - '0';
	return (converter(++str, result, sign));
}

int			ft_atoi(const char *str)
{
	if (!str || !*str)
		return (0);
	while (ft_strchr("\f\n\r\t\v ", *str))
		str++;
	if ((*str == '+' && ft_isdigit(str[1])) || ft_isdigit(*str))
		return (*str == '+' ? converter(&str[1], 0, 1) : converter(str, 0, 1));
	if (*str == '-' && ft_isdigit(str[1]))
		return (converter(&str[1], 0, -1));
	return (0);
}
