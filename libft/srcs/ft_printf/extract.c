/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:40:22 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/18 01:07:13 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		extract_flags(char **spec, t_format *format, va_list args)
{
	if (!ft_strchr(FLAGS, **spec))
		return ;
	if (**spec == '-' && (format->flag_minus = 1))
		format->flag_zero = 0;
	else if (**spec == '+' && (format->flag_plus = 1))
		format->flag_space = 0;
	else if (**spec == '@' && !format->flag_color && (format->flag_color = 1))
	{
		format->color = va_arg(args, char *);
		format->color = format->color ? ft_strjoin(FGCOL, format->color) : NULL;
	}
	else if (**spec == '0' && !format->flag_minus && format->flag_zero == 0)
		format->flag_zero = ft_strchr(*spec, '.') ? -1 : 1;
	else if (**spec == ' ' && !format->flag_plus)
		format->flag_space = 1;
	else if (**spec == '#')
		format->flag_hashtag = 1;
	format->diff++;
	*spec += 1;
	return (extract_flags(spec, format, args));
}

void		extract_width(char **spec, t_format *format, va_list args)
{
	if (**spec == '*')
	{
		format->width = va_arg(args, int);
		if (format->width < 0)
		{
			format->flag_minus = 1;
			format->width *= -1;
		}
		*spec += 1;
		format->diff++;
	}
	else
	{
		format->width = ft_atoi(*spec);
		while (ft_isdigit(**spec))
		{
			*spec += 1;
			format->diff++;
		}
	}
}

void		extract_precision(char **spec, t_format *format, va_list args)
{
	size_t		point;

	if (**spec != '.')
		return ;
	point = ft_strspn(*spec, ".");
	*spec += point;
	format->diff += point;
	if (**spec == '*')
	{
		format->precision = va_arg(args, int);
		format->diff++;
		*spec += 1;
	}
	else
	{
		format->precision = ft_atoi(*spec);
		while (ft_isdigit(**spec))
		{
			*spec += 1;
			format->diff++;
		}
	}
	return (extract_precision(spec, format, args));
}

void		extract_size(char **spec, t_format *format)
{
	int		len;

	len = ft_strspn(*spec, SIZE);
	format->size = ft_strsub(*spec, 0, len);
	format->diff += len;
	*spec += len;
	if (ft_strequ(format->size, "hh"))
		format->valid = 1;
	else if (ft_strequ(format->size, "h"))
		format->valid = 1;
	else if (ft_strequ(format->size, "l"))
		format->valid = 1;
	else if (ft_strequ(format->size, "ll"))
		format->valid = 1;
	else if (ft_strequ(format->size, "z"))
		format->valid = 1;
	else if (ft_strequ(format->size, "j"))
		format->valid = 1;
	else if (ft_strequ(format->size, "t"))
		format->valid = 1;
	else
		format->valid = 0;
}

int			extract_type(char **spec, t_format *format, va_list args)
{
	format->type = ft_strchr(TYPE, **spec) || **spec == '%' ? **spec : 0;
	if (!format->type)
		return (0);
	format->diff++;
	if (ft_strchr(OTHER, format->type))
		type_other(format, args);
	else if (ft_strchr(SIGNED, format->type))
	{
		format->precision = format->precision == -1 ? 1 : format->precision;
		type_signed_integer(format, args);
	}
	else if (ft_strchr(UNSIGNED, format->type))
	{
		format->precision = format->precision == -1 ? 1 : format->precision;
		type_unsigned_integer(format, args);
		if (format->flag_hashtag && !format->arg.u_character)
			format->flag_hashtag = ft_strchr("Oo", format->type) ? 1 : 0;
	}
	else if (ft_strchr(FLOAT, format->type))
		type_float(format, args);
	return (1);
}
