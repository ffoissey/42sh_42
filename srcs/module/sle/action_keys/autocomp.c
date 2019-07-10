/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 14:53:52 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static inline void		handle_void_comp(t_registry *shell, t_sle *sle,
				char *substring)
{
	ft_putendl_fd("", 2);
	update_window(sle);
	print_prompt(shell, sle);
	set_redraw_flags(sle, RD_LINE | RD_CMOVE);
	set_cursor_pos(sle, sle->cursor.index + ft_strlen(substring));
	ft_strdel(&substring);
}

static inline void		handle_work_comp(t_sle *sle,
				char *ret_completion, char *substring)
{
	vct_insert_string(sle->line, ret_completion, sle->cursor.index);
	set_redraw_flags(sle, RD_LINE | RD_CMOVE);
	set_cursor_pos(sle, sle->cursor.index + ft_strlen(ret_completion));
	ft_strdel(&ret_completion);
	ft_strdel(&substring);
}

int8_t					ak_hightab(t_registry *shell, t_sle *sle)
{
	char		*ret_completion;
	char		*substring;

	(void)shell;
	if (sle->state != STATE_STD)
		return (FAILURE);
	ret_completion = NULL;
	substring = ft_strdup(vct_get_string(sle->line));
	if (substring != NULL && ft_strlen(substring) > sle->cursor.index)
		substring[sle->cursor.index] = '\0';
	if (autocompletion(substring, shell,
			&ret_completion, NEW_SEARCH) == NOT_FOUND)
	{
		ft_strdel(&substring);
		return (FAILURE);
	}
	if (ret_completion != NULL)
		handle_work_comp(sle, ret_completion, substring);
	else
		handle_void_comp(shell, sle, substring);
	set_redraw_bounds(sle, sle->cursor.index == 0 ? 0
			: sle->cursor.index - 1, vct_len(sle->line));
	return (SUCCESS);
}
