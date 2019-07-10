/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_word_jumping_ak.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:22:09 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t		ak_ctrl_right(t_registry *shell, t_sle *sle)
{
	uint32_t		next_char;

	(void)shell;
	if (sle->state != STATE_STD && sle->state != STATE_VISUAL)
		return (FAILURE);
	if (sle->cursor.index == vct_len(sle->line))
		return (FAILURE);
	next_char = get_next_char(sle->line->buffer,
			sle->cursor.index, 1);
	if (sle->state == STATE_VISUAL)
		set_redraw_flags(sle, RD_LINE | RD_CMOVE);
	else
		set_redraw_flags(sle, RD_NONE | RD_CMOVE);
	set_cursor_pos(sle, next_char);
	find_multiline_coord(sle, next_char - sle->cursor.index);
	if (sle->state == STATE_VISUAL)
		sle->vis_stop = next_char;
	return (SUCCESS);
}

int8_t		ak_ctrl_left(t_registry *shell, t_sle *sle)
{
	int32_t		next_char;

	(void)shell;
	if (sle->state != STATE_STD && sle->state != STATE_VISUAL)
		return (FAILURE);
	next_char = get_next_char(sle->line->buffer, sle->cursor.index, -1);
	if (sle->state == STATE_VISUAL)
		set_redraw_flags(sle, RD_LINE | RD_CMOVE);
	else
		set_redraw_flags(sle, RD_NONE | RD_CMOVE);
	set_cursor_pos(sle, next_char);
	find_multiline_coord(sle, next_char - sle->cursor.index);
	if (sle->state == STATE_VISUAL && next_char >= 0)
		sle->vis_stop = next_char;
	return (SUCCESS);
}

int8_t		ak_ctrl_down(t_registry *shell, t_sle *sle)
{
	(void)shell;
	if (sle->state != STATE_STD && sle->state != STATE_VISUAL)
		return (FAILURE);
	if (sle->state == STATE_VISUAL)
		set_redraw_flags(sle, RD_LINE | RD_CMOVE);
	else
		set_redraw_flags(sle, RD_NONE | RD_CMOVE);
	set_cursor_pos(sle, sle->cursor.index
			+ sle->window.cols);
	find_multiline_coord(sle, sle->window.cols);
	if (sle->state == STATE_VISUAL
		&& (sle->cursor.index + sle->window.cols <= vct_len(sle->line) + 2))
		sle->vis_stop = (sle->cursor.index + sle->window.cols);
	return (SUCCESS);
}

int8_t		ak_ctrl_up(t_registry *shell, t_sle *sle)
{
	(void)shell;
	if (sle->state != STATE_STD && sle->state != STATE_VISUAL)
		return (FAILURE);
	if (sle->state == STATE_VISUAL)
		set_redraw_flags(sle, RD_LINE | RD_CMOVE);
	else
		set_redraw_flags(sle, RD_NONE | RD_CMOVE);
	set_cursor_pos(sle, sle->cursor.index - sle->window.cols);
	find_multiline_coord(sle, -sle->window.cols);
	if (sle->state == STATE_VISUAL)
		sle->vis_stop = (sle->cursor.index - sle->window.cols);
	return (SUCCESS);
}
