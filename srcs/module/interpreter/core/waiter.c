/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:36:20 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <stdio.h>

static void		update_pid(t_job *job, pid_t pid, int status)
{
	t_list			*processes;
	t_process		*current;

	processes = job->processes;
	while (processes)
	{
		current = processes->data;
		if (current->pid == pid)
			return (set_status(job, current, status));
		processes = processes->next;
	}
	return ;
}

static uint8_t	all_is_done(t_list *processes)
{
	t_process	*current;
	uint16_t	errors;

	errors = (IS_EXP_ERROR | IS_OPEN_FAILED
			| IS_CRITICAL | IS_DUP_FAILED | IS_ASSIGN);
	while (processes)
	{
		current = processes->data;
		if (current->type & ~(errors))
		{
			if (current->completed == FALSE && current->stopped == FALSE)
				return (FALSE);
		}
		processes = processes->next;
	}
	return (TRUE);
}

int				kill_process(void *context, void *data)
{
	uint32_t	*signo;
	t_process	*process;

	signo = context;
	process = data;
	if (process->completed == FALSE)
		kill(process->pid, *signo);
	return (SUCCESS);
}

void			update_last_bin(t_list *processes)
{
	char		*status;
	t_process	*last;
	uint16_t	errors;

	errors = (IS_EXP_ERROR | IS_OPEN_FAILED
			| IS_CRITICAL | IS_DUP_FAILED | IS_ASSIGN);
	if (processes == NULL)
		return ;
	while (processes->next != NULL)
		processes = processes->next;
	last = processes->data;
	if (last->type & ~(errors))
	{
		status = ft_itoa(last->status);
		add_var(&g_shell->intern, "?", status, READONLY_VAR);
		ft_strdel(&status);
	}
}

int8_t			waiter(t_job *job)
{
	int				status;
	pid_t			pid;

	while (all_is_done(job->processes) == FALSE)
	{
		if (job->state & KILLED)
			ft_lstiter_ctx(job->processes, &job->signo, kill_process);
		status = 0;
		pid = waitpid(-job->pgid, &status, WUNTRACED);
		if (pid)
			update_pid(job, pid, status);
	}
	update_last_bin(job->processes);
	job->state ^= (RUNNING | ENDED);
	tcsetpgrp(STDIN_FILENO, g_shell->pid);
	return (SUCCESS);
}
