/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 14:51:39 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t		ak_ctrl_t(t_registry *shell, t_sle *sle)
{
	(void)shell;
	if (sle->state != STATE_STD && sle->state != STATE_REVSEARCH)
		return (FAILURE);
	sle->state = STATE_INCSEARCH;
	sle->search_type = NEXT;
	set_redraw_flags(sle, RD_LINE | RD_CEND);
	return (SUCCESS);
}

int8_t		ak_ctrl_r(t_registry *shell, t_sle *sle)
{
	(void)shell;
	if (sle->state != STATE_STD && sle->state != STATE_INCSEARCH)
		return (FAILURE);
	sle->state = STATE_REVSEARCH;
	sle->search_type = PREV;
	set_redraw_flags(sle, RD_LINE | RD_CEND);
	return (SUCCESS);
}
