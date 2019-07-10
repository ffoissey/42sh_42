/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 13:38:49 by nrechati          #+#    #+#             */
/*   Updated: 2019/02/03 12:28:17 by cedricmpa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <limits.h>

static long double	flag_create(t_format *format, char *flag)
{
	long double value;

	if (ft_strequ(format->size, "l"))
		value = format->arg.l_double;
	else
		value = format->arg.s_double;
	if (format->flag_plus || value < 0)
		*flag = value < 0 ? '-' : '+';
	return (*flag == '-' && value != LONG_MIN ? -value : value);
}

static char			*round_double(long double value)
{
	int		prev;
	int		curr;
	int		diff;
	char	*holder;

	prev = (int)value;
	value *= 10;
	curr = (int)value;
	value *= 10;
	diff = (int)value - (curr * 10);
	if (diff >= 5)
		holder = ft_itoa(curr - (prev * 10) + 1);
	else
		holder = ft_itoa(curr - (prev * 10));
	return (holder);
}

static void			fill_float(t_format *format, char **tmp, long double value)
{
	int		i;
	int		prev;
	int		curr;
	char	*holder;

	i = -1;
	while (++i < format->precision - 1)
	{
		prev = (int)value;
		value *= 10;
		curr = (int)value;
		holder = ft_itoa(curr - (prev * 10));
		*tmp = ft_strinsert(tmp, *holder, ft_strlen(*tmp));
	}
	holder = round_double(value);
	*tmp = ft_strinsert(tmp, *holder, ft_strlen(*tmp));
	return ;
}

void				doubles(t_format *format)
{
	char		flag;
	char		*tmp;
	long double	value;

	flag = ' ';
	tmp = NULL;
	value = flag_create(format, &flag);
	tmp = ft_itoa(value);
	tmp = ft_strinsert(&tmp, '.', ft_strlen(tmp));
	fill_float(format, &tmp, value);
	format->width = format->width - ft_strlen(tmp);
	if (format->flag_plus || format->flag_space || flag == '-')
	{
		if (format->flag_minus || (format->flag_zero))
			format->width -= 1;
	}
	if (format->width > 0)
		tmp = width(format, tmp);
	if (format->flag_plus || format->flag_space || flag == '-')
		tmp = signing(format, tmp, flag);
	format->output = tmp;
	return ;
}
