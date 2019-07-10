/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:28:43 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

uint8_t			jobctl_is_active(t_registry *shell)
{
	if ((shell->option.option & INTERACTIVE_OPT) == FALSE)
	{
		ft_dprintf(2, "42sh: No job control.\n");
		return (FALSE);
	}
	return (TRUE);
}

t_job			*find_job(pid_t pgid)
{
	t_list *job;

	job = g_shell->job_list;
	while (job != NULL)
	{
		if (((t_job*)job->data)->pgid == pgid)
			return (job->data);
		job = job->next;
	}
	return (NULL);
}

uint8_t			job_is_stopped(t_job *job)
{
	t_list	*process;

	process = job->processes;
	while (process != NULL)
	{
		if (((t_process*)process->data)->completed == FALSE
						&& ((t_process*)process->data)->stopped == FALSE)
			return (FALSE);
		process = process->next;
	}
	return (TRUE);
}

uint8_t			job_is_completed(t_job *job)
{
	t_list	*process;

	process = job->processes;
	while (process != NULL)
	{
		if (((t_process*)process->data)->completed == FALSE)
			return (FALSE);
		process = process->next;
	}
	return (TRUE);
}

int8_t			am_i_forked(t_registry *shell, char *name)
{
	if (getpid() == shell->pid)
		return (FALSE);
	ft_dprintf(2, "42sh: %s: no job control.\n", name);
	return (TRUE);
}
