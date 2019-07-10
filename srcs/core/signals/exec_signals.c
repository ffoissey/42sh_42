/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 16:41:13 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	sigstop_exec(int signo)
{
	t_list		*job_lst;

	job_lst = *ptr_to_job_lst(NULL, GET_ADDR);
	ft_lstiter_ctx(job_lst, &signo, set_signaled);
}

void	init_exec_signals(void)
{
	signal(SIGHUP, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGCONT, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
}

void	sigchld_exec(int signo)
{
	(void)signo;
}

void	sigtstp_exec(int signo)
{
	(void)signo;
}

void	sigttin_exec(int signo)
{
	(void)signo;
}
