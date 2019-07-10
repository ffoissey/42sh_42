/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_clipboard_copy_ak.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:22:59 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	ak_copy_selection(t_registry *shell, t_sle *sle)
{
	char			*tmp;
	uint64_t		start;
	uint64_t		length;

	if (sle->state != STATE_VISUAL)
		return (FAILURE);
	start = (sle->vis_stop < sle->vis_start) ? sle->vis_stop : sle->vis_start;
	length = (sle->vis_stop < sle->vis_start)
			? (sle->vis_start - sle->vis_stop)
			: (sle->vis_stop - sle->vis_start);
	vct_reset(sle->clip);
	tmp = vct_sub(sle->line, start, length);
	vct_scpy(sle->clip, tmp, ft_strlen(tmp));
	ft_strdel(&tmp);
	ak_exit_modes(shell, sle);
	set_redraw_flags(sle, RD_LINE | RD_CMOVE);
	set_cursor_pos(sle, start);
	find_multiline_coord(sle, 0);
	return (SUCCESS);
}
