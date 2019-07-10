/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_sle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:33:35 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <termcap.h>

uint8_t				launch_sle(t_registry *shell, t_sle *sle)
{
	static uint64_t		setup_report = 0;

	if ((setup_report & SETUP_DONE) == FALSE)
	{
		shell->option.option |= RECORD_HISTORY_OPT;
		history(shell, NULL, INIT_HISTORY);
		setup_report = sle_setup(shell, sle);
		if (setup_report & CRITICAL_ERROR)
			return (CRITICAL_ERROR);
	}
	if (g_shell->job_notified == 1)
		g_shell->job_notified++;
	else
		g_shell->job_notified = 0;
	save_intern_vars(shell, sle);
	return (SUCCESS);
}

void				handle_cc(t_registry *shell, t_sle *sl, uint32_t flag)
{
	ak_exit_modes(shell, sl);
	history(NULL, NULL, RESET_HEAD);
	find_multiline_coord(sl, sl->cursor.index);
	set_redraw_flags(sl, RD_NONE | RD_CMOVE);
	set_cursor_pos(sl, sl->cursor.index);
	redraw(shell, sl);
	find_multiline_coord(sl, sl->cursor.index);
	if (flag & SLE_CC)
		ft_putstr_fd("^C", 2);
	set_redraw_flags(sl, RD_NONE | RD_CEND);
	redraw(shell, sl);
	ft_putendl_fd("", 2);
	update_window(sl);
	vct_reset(sl->line);
	find_multiline_coord(sl, sl->cursor.index);
}

void				handle_resize(t_sle *sle)
{
	if (sle->state == STATE_REVSEARCH || sle->state == STATE_INCSEARCH)
	{
		vct_reset(sle->line);
		sle->state = STATE_STD;
	}
	redraw_window(sle);
	find_multiline_coord(sle, 0);
	set_cursor_pos(sle, sle->cursor.index);
}

static uint8_t		sle_get_input(t_registry *shell, t_sle *sle, t_vector **in)
{
	sle->prompt.state = INT_PS1;
	*in = prompt(shell, sle);
	if (*in == NULL || is_eof(vct_get_string(*in)))
	{
		vct_del(in);
		return (FAILURE);
	}
	if (ft_strequ(vct_get_string(*in), "\0"))
		return (LINE_FAIL);
	return (SUCCESS);
}

uint8_t				sle(t_registry *shell, t_vector **in, uint32_t sle_flag)
{
	static t_sle		sle;

	if (launch_sle(shell, &sle) == CRITICAL_ERROR)
		return (CRITICAL_ERROR);
	load_signal_profile(SLE_PROFILE);
	term_mode(TERMMODE_SLE);
	if (sle_flag != SLE_SIZE_UPDATE)
		sle.state = STATE_STD;
	if (sle_flag == SLE_GET_INPUT)
		return (sle_get_input(shell, &sle, in));
	else if (sle_flag & SLE_PS2_PROMPT)
		*in = invoke_ps2prompt(shell, &sle, sle_flag);
	else if (sle_flag & SLE_PS3_PROMPT)
		*in = invoke_ps3prompt(shell, &sle);
	else if (sle_flag & SLE_RD_PROMPT)
		handle_cc(g_shell, &sle, sle_flag);
	else if (sle_flag & SLE_SIZE_UPDATE)
		handle_resize(&sle);
	else if (sle_flag == SLE_EXIT)
		sle_teardown(&sle);
	return (SUCCESS);
}
