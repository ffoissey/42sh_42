/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_keys.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:13:31 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void			insert_zero(t_sle *sle, char c[READ_SIZE])
{
	uint8_t		idx;

	idx = 0;
	while (idx < READ_SIZE)
	{
		if (ft_isprint(c[idx]))
			vct_add(sle->line, c[idx]);
		else
			break ;
		idx++;
	}
	set_redraw_flags(sle, RD_LINE | RD_CEND);
}

static void			handle_insertion(t_sle *sle, char c[READ_SIZE])
{
	t_cursor	*cursor;
	t_vector	*line;
	uint8_t		buff_len;

	line = sle->line;
	cursor = &sle->cursor;
	buff_len = ft_strlen(c);
	vct_insert_string(line, c, cursor->index);
	set_redraw_flags(sle, RD_LINE | RD_CMOVE);
	set_cursor_pos(sle, cursor->index + buff_len);
	find_multiline_coord(sle, 1);
}

static void			handle_printable_char(t_sle *sle, char c[READ_SIZE])
{
	uint8_t		buff_len;
	t_vector	*line;
	t_cursor	*cursor;

	cursor = &sle->cursor;
	line = sle->line;
	buff_len = ft_strlen(c);
	if (sle->state == STATE_INCSEARCH || sle->state == STATE_REVSEARCH)
		insert_zero(sle, c);
	else if (cursor->index == 0)
	{
		vct_insert_string(line, c, 0);
		set_redraw_flags(sle, RD_LINE | RD_CMOVE);
		set_cursor_pos(sle, buff_len);
		find_multiline_coord(sle, buff_len);
	}
	else if (cursor->index == vct_len(line))
	{
		vct_insert_string(line, c, cursor->index);
		set_redraw_flags(sle, RD_LINE | RD_CEND);
		set_cursor_pos(sle, vct_len(line));
		find_multiline_coord(sle, 1);
	}
	else
		handle_insertion(sle, c);
}

static void			handle_actionkey(t_registry *shell,
				t_sle *sle, char c[READ_SIZE])
{
	uint32_t	index;
	uint64_t	value;

	index = 0;
	value = compute_mask(c);
	while (index < AK_AMOUNT)
	{
		if (value == sle->ak_masks[index])
			sle->actionkeys[index](shell, sle);
		++index;
	}
}

void				handle_input_key(t_registry *shell,
				t_sle *sle, char c[READ_SIZE])
{
	if (is_printable(c) == TRUE)
	{
		if (sle->state != STATE_STD && sle->state != STATE_INCSEARCH
				&& sle->state != STATE_REVSEARCH)
			return ;
		handle_printable_char(sle, c);
		history(NULL, NULL, RESET_HEAD);
		vct_del(&sle->line_save);
	}
	else
		handle_actionkey(shell, sle, c);
}
