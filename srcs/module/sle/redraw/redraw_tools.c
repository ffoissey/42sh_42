/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 09:48:40 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <termcap.h>

void			index_to_coord(t_sle *sle, uint64_t index, t_coord *co)
{
	if (sle->window.cols == 0)
		return ;
	if (index > sle->rd_info.line_len + sle->rd_info.prompt_len + 1)
		index = sle->rd_info.line_len + sle->rd_info.prompt_len;
	if (sle->window.cols != 0)
	{
		co->x = (index % sle->window.cols);
		co->y = (index / sle->window.cols);
	}
}

void			print_char(t_sle *sle, char c)
{
	write(2, &c, 1);
	sle->cursor.x++;
	sle->cursor.index++;
	if (sle->cursor.x == sle->window.cols || c == '\n')
	{
		if (c != '\n')
			tputs(sle->termcaps.down, 2, &ft_putc);
		sle->cursor.y++;
		sle->cursor.x = 0;
	}
}

static void		print_loop_extend(t_sle *sle, char *str)
{
	size_t		i;
	int			active;

	i = 0;
	active = FALSE;
	while (str[i] != '\0')
	{
		if (sle->state == STATE_VISUAL && i >= sle->window.point1
				&& i < sle->window.point2)
		{
			tputs(sle->termcaps.standout_on, 1, &ft_putc);
			active = TRUE;
		}
		else if (active == TRUE)
		{
			tputs(sle->termcaps.standout_off, 1, &ft_putc);
			active = FALSE;
		}
		print_char(sle, str[i++]);
	}
	tputs(sle->termcaps.standout_off, 1, &ft_putc);
}

void			print_loop(t_sle *sle, char *str)
{
	tputs(sle->termcaps.normal_cursor, 1, &ft_putc);
	if (sle->state == STATE_REVSEARCH || sle->state == STATE_INCSEARCH
		|| (sle->state == STATE_VISUAL
		&& sle->window.point1 - sle->window.point2 != 0))
		tputs(sle->termcaps.hidden_cursor, 1, &ft_putc);
	print_loop_extend(sle, str);
}
