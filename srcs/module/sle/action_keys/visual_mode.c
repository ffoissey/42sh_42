/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 15:44:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <termcap.h>

int8_t					ak_enter_visual_mode(t_registry *shell, t_sle *sle)
{
	(void)shell;
	if (sle->state != STATE_STD)
		return (FAILURE);
	sle->state = STATE_VISUAL;
	sle->vis_start = sle->cursor.index;
	sle->vis_stop = sle->cursor.index;
	return (SUCCESS);
}

int8_t					ak_exit_modes(t_registry *shell, t_sle *sle)
{
	(void)shell;
	sle->state = STATE_STD;
	set_redraw_flags(sle, RD_LINE | RD_CEND);
	return (SUCCESS);
}

static inline uint8_t	visual_bounds_valid(t_sle *sle)
{
	if (sle->vis_start < 0
		|| sle->vis_stop < 0
		|| (uint64_t)sle->vis_start > vct_len(sle->line)
		|| (uint64_t)sle->vis_stop > vct_len(sle->line))
		return (FALSE);
	return (TRUE);
}

void					redrawmode_visual(t_sle *sle)
{
	if (visual_bounds_valid(sle) == FALSE)
		return ;
	if (sle->vis_stop < sle->vis_start)
		set_redraw_bounds(sle, sle->vis_stop, sle->vis_start);
	else
		set_redraw_bounds(sle, sle->vis_start, sle->vis_stop);
}
