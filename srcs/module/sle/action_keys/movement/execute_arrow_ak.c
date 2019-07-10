/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_arrow_ak.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:21:29 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t				ak_arrow_right(t_registry *shell, t_sle *sle)
{
	int8_t offset;

	(void)shell;
	if (sle->state != STATE_STD && sle->state != STATE_VISUAL)
		return (FAILURE);
	offset = 1;
	if (sle->cursor.index >= vct_len(sle->line))
		offset = 0;
	if (sle->state == STATE_VISUAL)
		sle->vis_stop = sle->cursor.index + offset;
	set_cursor_pos(sle, sle->cursor.index + offset);
	if (sle->state == STATE_VISUAL)
		set_redraw_flags(sle, RD_LINE | RD_CMOVE);
	else
		set_redraw_flags(sle, RD_NONE | RD_CMOVE);
	find_multiline_coord(sle, offset);
	return (SUCCESS);
}

int8_t				ak_arrow_left(t_registry *shell, t_sle *sle)
{
	int8_t offset;

	(void)shell;
	if (sle->state != STATE_STD && sle->state != STATE_VISUAL)
		return (FAILURE);
	offset = -1;
	if (sle->cursor.index == 0)
		offset = 0;
	if (sle->state == STATE_VISUAL && sle->cursor.index > 0)
		sle->vis_stop = sle->cursor.index + offset;
	set_cursor_pos(sle, sle->cursor.index + offset);
	if (sle->state == STATE_VISUAL)
		set_redraw_flags(sle, RD_LINE | RD_CMOVE);
	else
		set_redraw_flags(sle, RD_NONE | RD_CMOVE);
	find_multiline_coord(sle, offset);
	return (SUCCESS);
}

int8_t				ak_arrow_up(t_registry *shell, t_sle *sle)
{
	uint64_t	len;
	char		*hist_cmd;

	(void)shell;
	if (sle->state != STATE_STD && sle->state != STATE_INCSEARCH
				&& sle->state != STATE_REVSEARCH)
		return (FAILURE);
	if (sle->state == STATE_STD && sle->line_save == NULL)
		sle->line_save = vct_dup(sle->line);
	if (sle->state == STATE_REVSEARCH || sle->state == STATE_INCSEARCH)
		sle->state = STATE_STD;
	hist_cmd = history(NULL, NULL, GET_ENTRY | PREV);
	if (hist_cmd == NULL)
		return (FAILURE);
	len = (vct_len(sle->line) == 0) ? 1 : vct_len(sle->line);
	vct_replace_string(sle->line, 0, len, hist_cmd);
	set_redraw_flags(sle, RD_LINE | RD_CEND);
	find_multiline_coord(sle, 0);
	return (SUCCESS);
}

int8_t				ak_arrow_down(t_registry *shell, t_sle *sle)
{
	char		*hist_cmd;
	uint64_t	len;

	(void)shell;
	if (sle->state != STATE_STD && sle->state != STATE_REVSEARCH
				&& sle->state != STATE_INCSEARCH)
		return (FAILURE);
	if (sle->state == STATE_REVSEARCH || sle->state == STATE_INCSEARCH)
		sle->state = STATE_STD;
	hist_cmd = history(NULL, NULL, GET_ENTRY | NEXT);
	len = (vct_len(sle->line) == 0) ? 1 : vct_len(sle->line);
	if (hist_cmd == NULL)
	{
		if (sle->line_save == NULL
			|| sle->line_save->buffer == NULL)
			return (FAILURE);
		history(NULL, NULL, RESET_HEAD);
		vct_replace_string(sle->line, 0, len, vct_get_string(sle->line_save));
		vct_del(&sle->line_save);
	}
	else
		vct_replace_string(sle->line, 0, len, hist_cmd);
	set_redraw_flags(sle, RD_LINE | RD_CEND);
	find_multiline_coord(sle, 0);
	return (SUCCESS);
}
