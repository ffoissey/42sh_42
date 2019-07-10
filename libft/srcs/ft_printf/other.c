/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 10:19:59 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/15 16:05:16 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include "ft_printf.h"

static char		*str_colors(t_format *format, char *tmp)
{
	char	*join;
	int		id;

	if (!format->color)
		return (tmp);
	join = NULL;
	if ((id = ft_strspn(tmp, " ")))
		ft_asprintf(&join, "%.*s%sm%s%s"
							, id, tmp, format->color, &tmp[id], END_COLOR);
	else if ((id = ft_strlen(format->arg.string)))
		ft_asprintf(&join, "%sm%.*s%s%s"
						, format->color, id, tmp, END_COLOR, &tmp[id]);
	format->color_len += ft_strlen(format->color) + ft_strlen(END_COLOR) + 1;
	ft_strdel(&tmp);
	return (join);
}

static char		*converter(t_format *format)
{
	char		*tmp;
	char		*dst;

	if (format->precision == 0 && format->arg.pointer == NULL)
		dst = NULL;
	else
	{
		tmp = ft_ullitoa((uintptr_t)format->arg.pointer);
		dst = ft_convert_base(tmp, TEN, HEXA);
		ft_strdel(&tmp);
	}
	tmp = ft_strjoin("0x", dst);
	ft_strdel(&dst);
	return (tmp);
}

void			pointer(t_format *format)
{
	char		*tmp;

	tmp = converter(format);
	format->width = format->width - ft_strlen(tmp);
	if (format->width > 0)
		tmp = width(format, tmp);
	if (format->flag_color)
		tmp = colors(format, tmp);
	format->output = tmp;
	return ;
}

void			string(t_format *format)
{
	char	*tmp;

	if (format->precision == -1)
		tmp = ft_strdup(format->arg.string);
	else
		tmp = ft_strsub(format->arg.string, 0, format->precision);
	format->width = format->width - ft_strlen(tmp);
	if (format->width > 0)
		tmp = width(format, tmp);
	if (format->flag_color)
		tmp = str_colors(format, tmp);
	format->output = tmp;
	return ;
}

void			character(t_format *format)
{
	char		*tmp;

	tmp = ft_strnew(1);
	*tmp = format->arg.character;
	format->width = format->width - 1;
	if (format->width > 0)
		tmp = width(format, tmp);
	if (format->flag_color)
		tmp = colors(format, tmp);
	format->output = tmp;
	return ;
}
