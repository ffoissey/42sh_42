/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw_modes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 10:26:30 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <termcap.h>

void			redrawmode_clear(t_registry *shell, t_sle *sle)
{
	tputs(sle->termcaps.clear, 1, &ft_putc);
	sle->cursor.x = 0;
	sle->cursor.y = 0;
	sle->cursor.index = 0;
	print_prompt(shell, sle);
}

void			redrawmode_last(t_sle *sle)
{
	t_coord		co;

	if (sle->rd_info.line_len >= sle->rd_info.disp_len)
	{
		index_to_coord(sle, sle->rd_info.prompt_len
						+ sle->rd_info.line_len - 1, &co);
		move_cursor_to_coord(sle, co.x, co.y);
		print_char(sle, vct_charat(sle->line,
						vct_len(sle->line) - 1));
	}
	else
	{
		index_to_coord(sle, sle->rd_info.prompt_len
						+ sle->rd_info.line_len - 1, &co);
		move_cursor_to_coord(sle, co.x, co.y);
		print_char(sle, ' ');
	}
}

static void		state_search(t_sle *sle)
{
	t_vector	*disp_line;
	char		*search_hit;

	disp_line = NULL;
	search_hit = NULL;
	vct_del(&sle->search_hit);
	sle->search_hit = NULL;
	tputs(sle->termcaps.hidden_cursor, 1, &ft_putc);
	search_hit = history(NULL, vct_get_string(sle->line),
		GET_ENTRY | BY_NAME | sle->search_type);
	sle->search_hit = vct_dups(search_hit);
	disp_line = vct_dups(((sle->state == STATE_INCSEARCH)
							? INC_SEARCH : REV_SEARCH));
	vct_ncat(disp_line, sle->line, vct_len(sle->line));
	vct_scat(disp_line, SEARCH_SUFFIX, ft_strlen(SEARCH_SUFFIX));
	if (search_hit == NULL && sle->line != NULL
		&& sle->line->buffer[0] != '\0')
		vct_scat(disp_line, "Failed", 6);
	else if (search_hit != NULL)
		vct_scat(disp_line, search_hit, ft_strlen(search_hit));
	else
		vct_scat(disp_line, "", 1);
	print_loop(sle, vct_get_string(disp_line));
	vct_del(&disp_line);
}

void			redrawmode_line(t_sle *sle)
{
	t_coord		co;

	index_to_coord(sle, sle->rd_info.prompt_len, &co);
	move_cursor_to_coord(sle, co.x, co.y);
	tputs(sle->termcaps.clear_screen, 1, &ft_putc);
	tputs(sle->termcaps.clear_line, 1, &ft_putc);
	if (sle->state == STATE_REVSEARCH || sle->state == STATE_INCSEARCH)
		state_search(sle);
	else
		print_loop(sle, vct_get_string(sle->line));
}

void			redrawmode_fptp(t_sle *sle)
{
	char		c;
	t_coord		co;
	int64_t		length;
	int64_t		tmp;

	index_to_coord(sle, sle->window.point1 + sle->rd_info.prompt_len, &co);
	move_cursor_to_coord(sle, co.x, co.y);
	length = sle->window.point2 - (sle->window.point1 + 1);
	tmp = sle->window.point1;
	while (length > 0)
	{
		if ((c = vct_charat(sle->line, tmp)) != 0)
			print_char(sle, c);
		else
			print_char(sle, ' ');
		++tmp;
		--length;
	}
}
