/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 12:40:24 by nrechati          #+#    #+#             */
/*   Updated: 2019/02/04 21:38:41 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*unsigned_convert(t_format *format)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strequ(format->size, "l") || ft_strchr("OU", format->type))
		tmp = ft_ullitoa(format->arg.ul_integer);
	else if (ft_strequ(format->size, "ll") || ft_strequ(format->size, "L"))
		tmp = ft_ullitoa(format->arg.ull_integer);
	else if (ft_strequ(format->size, "j"))
		tmp = ft_ullitoa(format->arg.u_intmax);
	else
		tmp = ft_ullitoa(format->arg.u_integer);
	if (*tmp == '0' && format->precision == 0)
		*tmp = '\0';
	return (tmp);
}

void	u_integer(t_format *format)
{
	char	*tmp;
	int		len;

	tmp = unsigned_convert(format);
	len = ft_strlen(tmp);
	if ((format->precision -= len) > 0)
		tmp = precision(format, tmp);
	format->width = format->width - ft_strlen(tmp);
	if (format->width > 0)
		tmp = width(format, tmp);
	if (format->flag_color)
		tmp = colors(format, tmp);
	format->output = tmp;
	return ;
}

void	hexadecimal(t_format *format)
{
	char	*tmp;
	char	*holder;

	tmp = unsigned_convert(format);
	holder = tmp;
	tmp = *holder ? ft_convert_base(tmp, TEN, HEXA) : tmp;
	if (*holder)
		ft_strdel(&holder);
	if ((format->precision -= ft_strlen(tmp)) > 0)
		tmp = precision(format, tmp);
	format->width = format->width - ft_strlen(tmp);
	if (format->flag_hashtag && (format->flag_zero || format->flag_minus))
		format->width -= 2;
	if (format->width > 0)
		tmp = width(format, tmp);
	if (format->flag_hashtag && *tmp)
		tmp = prefix(format, tmp);
	if (format->type == 'X')
		ft_strupper(tmp);
	if (format->flag_color)
		tmp = colors(format, tmp);
	format->output = tmp;
	return ;
}

void	octal(t_format *format)
{
	char	*tmp;
	char	*holder;
	int		len;

	tmp = unsigned_convert(format);
	holder = tmp;
	tmp = *holder ? ft_convert_base(tmp, TEN, OCTAL) : tmp;
	if (*holder)
		ft_strdel(&holder);
	len = ft_strlen(tmp);
	if (format->flag_hashtag)
		if (*tmp != '0')
			format->precision = ft_strlen(tmp) + 1;
	if ((format->precision -= len) > 0)
		tmp = precision(format, tmp);
	format->width = format->width - ft_strlen(tmp);
	if (format->width > 0)
		tmp = width(format, tmp);
	if (format->flag_color)
		tmp = colors(format, tmp);
	format->output = tmp;
	return ;
}

void	binary(t_format *format)
{
	char	*tmp;
	char	*holder;
	int		len;

	tmp = unsigned_convert(format);
	holder = tmp;
	tmp = *holder ? ft_convert_base(tmp, TEN, BINARY) : tmp;
	if (*holder)
		ft_strdel(&holder);
	len = ft_strlen(tmp);
	if ((format->precision -= len) > 0)
		tmp = precision(format, tmp);
	if (format->flag_hashtag && (holder = tmp))
		tmp = prefix(format, tmp);
	format->width = format->width - ft_strlen(tmp);
	if (format->width > 0)
		tmp = width(format, tmp);
	if (format->flag_color)
		tmp = colors(format, tmp);
	format->output = tmp;
	return ;
}
