/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 19:38:06 by cempassi          #+#    #+#             */
/*   Updated: 2019/06/30 07:30:05 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		format_init(t_format *format)
{
	format->id = 0;
	format->valid = 1;
	format->flag_minus = 0;
	format->flag_plus = 0;
	format->flag_zero = 0;
	format->flag_space = 0;
	format->flag_hashtag = 0;
	format->flag_color = 0;
	format->color_len = 0;
	format->type = 0;
	format->diff = 0;
	format->width = 0;
	format->precision = -1;
	format->size = NULL;
	format->output = NULL;
	format->convert = NULL;
}

static t_list	*parser(char *spec, va_list args)
{
	t_format	format;

	format_init(&format);
	if (spec)
	{
		spec++;
		format.diff += 1;
		if (ft_strchr(FLAGS, *spec))
			extract_flags(&spec, &format, args);
		if (ft_isdigit(*spec) || *spec == '*')
			extract_width(&spec, &format, args);
		if (*spec == '.')
			extract_precision(&spec, &format, args);
		if (ft_strchr(SIZE, *spec))
			extract_size(&spec, &format);
		if (ft_strchr(FLAGS, *spec))
			extract_flags(&spec, &format, args);
		format.valid = extract_type(&spec, &format, args);
	}
	else
		format.valid = 0;
	return (ft_lstnew(&format, sizeof(t_format)));
}

void			format_delete(void *data)
{
	t_format *format;

	format = (t_format *)data;
	if (format->type == 's')
		ft_strdel(&format->arg.string);
	if (format->flag_color)
		ft_strdel(&format->color);
	ft_strdel(&format->size);
	ft_strdel(&format->output);
}

t_list			*format_list(const char *format, va_list args)
{
	t_list			*lst;
	t_list			*node;
	char			*spec;

	lst = NULL;
	while (*format)
	{
		if (*format == '%')
		{
			spec = ft_strsub(format, 0, ft_strcspn(format, TYPE) + 1);
			node = parser(spec, args);
			((t_format *)(node->data))->id = (char)ft_lstlen(lst) + 1;
			ft_lstaddback(&lst, node);
			format += ((t_format *)(node->data))->diff;
			ft_strdel(&spec);
		}
		else
			format += ft_strcspn(format, "%");
	}
	return (lst);
}
