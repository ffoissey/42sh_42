/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 11:38:30 by nrechati          #+#    #+#             */
/*   Updated: 2019/06/30 06:24:01 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>

static char			*convert(t_format *format, long long value)
{
	char	*tmp;

	tmp = ft_llitoa(value);
	if (*tmp == '0' && format->precision == 0)
		*tmp = '\0';
	if (*tmp == '-')
	{
		format->output = tmp;
		tmp = ft_strsub(tmp, 1, ft_strlen(tmp));
		ft_strdel(&format->output);
	}
	return (tmp);
}

static long long	flag_create(t_format *format, char *flag)
{
	long long		value;

	if (ft_strequ(format->size, "hh"))
		value = format->arg.character;
	else if (ft_strequ(format->size, "h"))
		value = format->arg.s_short;
	else if (ft_strequ(format->size, "l") || format->type == 'D')
		value = format->arg.l_integer;
	else if (ft_strequ(format->size, "ll") || ft_strequ(format->size, "L"))
		value = format->arg.ll_integer;
	else if (ft_strequ(format->size, "t"))
		value = format->arg.ptrdiff;
	else if (ft_strchr(format->size, 'z'))
		value = format->arg.ssizet;
	else if (ft_strchr(format->size, 'j'))
		value = format->arg.intmax;
	else
		value = format->arg.integer;
	if (format->flag_plus || value < 0)
		*flag = value < 0 ? '-' : '+';
	return (*flag == '-' && value != LONG_MIN ? -value : value);
}

void				digit(t_format *format)
{
	char			*tmp;
	char			sign;
	long long		value;

	sign = ' ';
	value = flag_create(format, &sign);
	tmp = convert(format, value);
	if ((format->precision -= ft_strlen(tmp)) > 0)
	{
		format->flag_zero = 0;
		tmp = precision(format, tmp);
	}
	format->width = format->width - ft_strlen(tmp);
	if (format->flag_plus || format->flag_space || sign == '-')
		if (format->flag_minus || (*tmp == '0' && format->precision < 0))
			format->width -= 1;
	if (format->width > 0)
		tmp = width(format, tmp);
	if (format->flag_plus || format->flag_space || sign == '-')
		tmp = signing(format, tmp, sign);
	if (format->flag_color)
		tmp = colors(format, tmp);
	format->output = tmp;
	return ;
}
