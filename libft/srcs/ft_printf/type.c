/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 01:10:05 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/03 01:52:47 by cedricmpa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				type_signed_integer(t_format *format, va_list args)
{
	if (ft_strequ(format->size, "l") || format->type == 'D')
		format->arg.l_integer = va_arg(args, long int);
	else if (ft_strchr(format->size, 'j'))
		format->arg.intmax = va_arg(args, intmax_t);
	else if (ft_strequ(format->size, "hh"))
	{
		format->arg.integer = va_arg(args, int);
		format->arg.character = (char)format->arg.integer;
	}
	else if (ft_strequ(format->size, "h"))
	{
		format->arg.integer = va_arg(args, int);
		format->arg.s_short = (short)format->arg.integer;
	}
	else if (ft_strequ(format->size, "ll") || ft_strequ(format->size, "L"))
		format->arg.ll_integer = va_arg(args, long long int);
	else if (ft_strchr(format->size, 'z') || ft_strequ(format->size, "I"))
		format->arg.ssizet = va_arg(args, ssize_t);
	else if (ft_strequ(format->size, "t") || ft_strequ(format->size, "I"))
		format->arg.ptrdiff = va_arg(args, ptrdiff_t);
	else
		format->arg.integer = va_arg(args, int);
	format->convert = digit;
}

static t_convert	unsigned_converter(t_format *format)
{
	if (format->type == 'b')
		return (binary);
	if (format->type == 'o' || format->type == 'O')
		return (octal);
	if (format->type == 'x' || format->type == 'X')
		return (hexadecimal);
	else
		return (u_integer);
}

void				type_unsigned_integer(t_format *format, va_list args)
{
	if (ft_strequ(format->size, "l") || ft_strchr("OU", format->type))
		format->arg.ul_integer = va_arg(args, unsigned long int);
	else if (ft_strequ(format->size, "hh"))
	{
		format->arg.u_integer = va_arg(args, unsigned int);
		format->arg.u_character = (unsigned char)format->arg.u_integer;
	}
	else if (ft_strequ(format->size, "h"))
	{
		format->arg.u_integer = va_arg(args, unsigned int);
		format->arg.u_short = (unsigned short)format->arg.u_integer;
	}
	else if (ft_strequ(format->size, "ll") || ft_strequ(format->size, "L"))
		format->arg.ull_integer = va_arg(args, unsigned long long int);
	else if (ft_strequ(format->size, "j"))
		format->arg.u_intmax = va_arg(args, uintmax_t);
	else if (ft_strequ(format->size, "z") || ft_strequ(format->size, "I"))
		format->arg.sizet = va_arg(args, size_t);
	else if (ft_strequ(format->size, "t") || ft_strequ(format->size, "I"))
		format->arg.ptrdiff = va_arg(args, ptrdiff_t);
	else
		format->arg.u_integer = va_arg(args, int);
	format->convert = unsigned_converter(format);
}

void				type_float(t_format *format, va_list args)
{
	if (format->size == NULL)
		format->arg.s_double = va_arg(args, double);
	else if (ft_strequ(format->size, "l") || ft_strequ(format->size, "L"))
		format->arg.l_double = va_arg(args, long double);
	else if (ft_strequ(format->size, "l") || ft_strequ(format->size, "L"))
		format->arg.l_double = va_arg(args, long double);
	if (format->precision == -1)
		format->precision = 6;
	format->convert = doubles;
}

void				type_other(t_format *format, va_list args)
{
	if (format->type == 'c' || format->type == '%')
	{
		format->arg.integer = format->type == 'c' ? va_arg(args, int) : '%';
		format->arg.character = format->arg.integer;
		format->convert = character;
	}
	if (format->type == 's')
	{
		if ((format->arg.string = va_arg(args, char *)))
			format->arg.string = ft_strdup(format->arg.string);
		else
			format->arg.string = ft_strdup("(null)");
		format->convert = string;
	}
	if (format->type == 'p')
	{
		format->arg.pointer = va_arg(args, void *);
		format->convert = pointer;
	}
}
