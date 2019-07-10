/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signal_profile.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 18:23:42 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static struct sigaction	set_sigaction_struct(void (*handler)(int),
			int flags, sigset_t mask)
{
	struct sigaction	sigaction;

	sigaction.sa_handler = handler;
	sigaction.sa_flags = flags;
	sigaction.sa_mask = mask;
	return (sigaction);
}

static void				loop_defaults(struct sigaction generic[NB_SIGNALS])
{
	int			i;
	sigset_t	sigset;

	i = 1;
	ft_bzero(&sigset, sizeof(sigset_t));
	while (i < NB_SIGNALS)
	{
		generic[i] = set_sigaction_struct(SIG_DFL, SA_RESTART, sigset);
		++i;
	}
}

void					init_tab_signal_dflt(
							struct sigaction tab_signal[NB_SIGNALS])
{
	struct sigaction	ignore;
	sigset_t			sigset;

	ft_bzero(&sigset, sizeof(sigset_t));
	loop_defaults(tab_signal);
	ignore = set_sigaction_struct(SIG_IGN, SA_RESTART, sigset);
	tab_signal[SIGINT] = ignore;
	tab_signal[SIGTERM] = ignore;
	tab_signal[SIGQUIT] = ignore;
	tab_signal[SIGTSTP] = ignore;
	tab_signal[SIGCONT] = ignore;
}

void					init_tab_signal_sle(
							struct sigaction tab_signal[NB_SIGNALS])
{
	sigset_t			sigset;

	ft_bzero(&sigset, sizeof(sigset_t));
	loop_defaults(tab_signal);
	tab_signal[SIGQUIT] = set_sigaction_struct(SIG_IGN, SA_RESTART, sigset);
	tab_signal[SIGTERM] = set_sigaction_struct(sigterm_sle, SA_RESTART,
								sigset);
	tab_signal[SIGCONT] = set_sigaction_struct(SIG_IGN, SA_RESTART, sigset);
	tab_signal[SIGTSTP] = set_sigaction_struct(SIG_IGN, SA_RESTART, sigset);
	tab_signal[SIGTTIN] = set_sigaction_struct(SIG_IGN, SA_RESTART, sigset);
	tab_signal[SIGTTOU] = set_sigaction_struct(SIG_IGN, SA_RESTART, sigset);
	tab_signal[SIGPIPE] = set_sigaction_struct(SIG_DFL, 0, sigset);
	tab_signal[SIGINT] = set_sigaction_struct(sigint_sle, 0, sigset);
	tab_signal[SIGWINCH] = set_sigaction_struct(sigwinch_sle, SA_RESTART,
								sigset);
}

void					init_tab_signal_exec(
							struct sigaction tab_signal[NB_SIGNALS])
{
	sigset_t			sigset;

	ft_bzero(&sigset, sizeof(sigset_t));
	loop_defaults(tab_signal);
	tab_signal[SIGHUP] = set_sigaction_struct(SIG_IGN, SA_RESTART, sigset);
	tab_signal[SIGINT] = set_sigaction_struct(sigstop_exec, SA_RESTART, sigset);
	tab_signal[SIGQUIT] = set_sigaction_struct(sigstop_exec, SA_RESTART,
								sigset);
	tab_signal[SIGTERM] = set_sigaction_struct(sigstop_exec, SA_RESTART,
								sigset);
	tab_signal[SIGTSTP] = set_sigaction_struct(SIG_IGN, SA_RESTART, sigset);
	tab_signal[SIGCONT] = set_sigaction_struct(SIG_IGN, SA_RESTART, sigset);
	tab_signal[SIGTTIN] = set_sigaction_struct(SIG_IGN, SA_RESTART, sigset);
	tab_signal[SIGTTOU] = set_sigaction_struct(SIG_IGN, SA_RESTART, sigset);
	tab_signal[SIGPIPE] = set_sigaction_struct(SIG_DFL, 0, sigset);
	tab_signal[SIGCHLD] = set_sigaction_struct(sigchld_exec, SA_RESTART,
								sigset);
}
