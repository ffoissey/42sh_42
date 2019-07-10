/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sle_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:44:22 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	sigterm_sle(int signo)
{
	(void)signo;
	exit_blt(g_shell->intern, 0);
}

void	sigcont_sle(int signo)
{
	(void)signo;
}

void	sigtstp_sle(int signo)
{
	(void)signo;
}

void	sigint_sle(int signo)
{
	(void)signo;
	g_shell->sigint = TRUE;
	add_var(&g_shell->intern, "?", "130", READONLY_VAR);
	sle(NULL, NULL, SLE_RD_PROMPT | SLE_CC);
}

void	sigwinch_sle(int signo)
{
	(void)signo;
	sle(NULL, NULL, SLE_SIZE_UPDATE);
}
