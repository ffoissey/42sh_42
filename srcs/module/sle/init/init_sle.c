/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:36:14 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <termcap.h>

uint64_t			get_terminal_info(t_registry *shell)
{
	char	*terminal;

	terminal = NULL;
	terminal = getenv("TERM");
	if (terminal == NULL || ft_strequ(terminal, ""))
	{
		terminal = INT_TERM_DFLT_VALUE;
		add_var(&shell->intern, INT_TERM,
						INT_TERM_DFLT_VALUE, SET_VAR | EXPORT_VAR);
	}
	else
		add_var(&shell->intern, INT_TERM, terminal, SET_VAR | EXPORT_VAR);
	if (tgetent(NULL, terminal) == FAILURE)
		return (CRITICAL_ERROR | INVALID_TERM);
	return (SUCCESS);
}

static uint64_t		validate_termcaps(t_termcaps *tc)
{
	uint64_t	error;

	error = 0;
	error += (tc->clear_line == NULL) ? 1 : 0;
	error += (tc->clear_screen == NULL) ? 1 : 0;
	error += (tc->standout_on == NULL) ? 1 : 0;
	error += (tc->standout_off == NULL) ? 1 : 0;
	error += (tc->clear == NULL) ? 1 : 0;
	error += (tc->up == NULL) ? 1 : 0;
	error += (tc->down == NULL) ? 1 : 0;
	error += (tc->left == NULL) ? 1 : 0;
	error += (tc->right == NULL) ? 1 : 0;
	error += (tc->hidden_cursor == NULL) ? 1 : 0;
	error += (tc->normal_cursor == NULL) ? 1 : 0;
	return ((error != 0) ? (CRITICAL_ERROR | INVALID_TERMCAPS) : SUCCESS);
}

uint64_t			init_termcaps(t_termcaps *termcap)
{
	termcap->clear_line = ft_strdup(tgetstr("ce", NULL));
	termcap->clear_screen = ft_strdup(tgetstr("cd", NULL));
	termcap->standout_on = ft_strdup(tgetstr("so", NULL));
	termcap->standout_off = ft_strdup(tgetstr("se", NULL));
	termcap->clear = ft_strdup(tgetstr("cl", NULL));
	termcap->up = ft_strdup(tgetstr("up", NULL));
	termcap->down = ft_strdup(tgetstr("do", NULL));
	termcap->left = ft_strdup(tgetstr("le", NULL));
	termcap->right = ft_strdup(tgetstr("nd", NULL));
	termcap->hidden_cursor = ft_strdup(tgetstr("vi", NULL));
	termcap->normal_cursor = ft_strdup(tgetstr("ve", NULL));
	return (validate_termcaps(termcap));
}
