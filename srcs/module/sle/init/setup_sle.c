/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_sle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:36:34 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void					sle_error(uint64_t report)
{
	if (report & CRITICAL_ERROR)
		ft_dprintf(2, "42sh: One or more critical error occured: \n");
	else if (report != (SUCCESS | SETUP_DONE))
		ft_dprintf(2, "42sh: warning: some errors occured: \n");
	if (report != (SUCCESS | SETUP_DONE))
		ft_dprintf(2, "Error code: %lu. See logs.\n", report);
}

static uint64_t			init_sle(t_registry *shell, t_sle *sle)
{
	uint64_t		report;

	report = 0;
	report |= get_terminal_info(shell);
	report |= term_mode(TERMMODE_SLE);
	report |= init_termcaps(&sle->termcaps);
	return (report);
}

static uint64_t			load_interface(t_registry *shell, t_sle *sle)
{
	uint64_t		report;

	report = 0;
	ft_memset(&sle->interns, 0, sizeof(t_intern));
	report |= assign_keycodes(sle);
	report |= link_keys_functions(sle->actionkeys);
	report |= set_sle_internals(shell);
	report |= init_line(sle);
	ft_memset(&sle->window, 0, sizeof(t_window));
	ft_memset(&sle->cursor, 0, sizeof(t_cursor));
	ft_memset(&sle->prompt, 0, sizeof(t_prompt));
	report |= init_window(sle);
	report |= init_cursor(sle);
	report |= init_prompt(sle);
	return (report);
}

uint64_t				sle_setup(t_registry *shell, t_sle *sle)
{
	uint64_t		report;

	report = 0;
	report |= init_sle(shell, sle);
	report |= load_interface(shell, sle);
	sle->state = STATE_STD;
	report |= SETUP_DONE;
	sle_error(report);
	return (report);
}
