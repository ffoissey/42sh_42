/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 17:59:16 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		print_longformat(t_job *job, char *state)
{
	char		*avs;
	t_process	*proc;
	t_list		*process;

	proc = job->processes->data;
	get_process_av(proc, &avs);
	ft_printf("[%d]%c %d %s:%d \t %s\n", job->id, job->current,
				(uint32_t)job->pgid, state, job->signo,
				avs);
	ft_strdel(&avs);
	process = job->processes->next;
	while (process != NULL)
	{
		get_process_av(process->data, &avs);
		ft_printf("      %d \t \t| %s\n",
						(uint32_t)((t_process*)process->data)->pid,
						avs);
		ft_strdel(&avs);
		process = process->next;
	}
}

static void		print_jobinfo(t_job *job, uint8_t flag)
{
	char		*state;
	char		*command;

	state_to_str(job, &state);
	get_job_av(job, &command);
	if (flag & JOBCTL_LONG)
		print_longformat(job, state);
	else if (flag & JOBCTL_ID)
		ft_printf("%d\n", job->pgid);
	else
		ft_printf("[%d]%c %s \t %s\n", job->id, job->current, state, command);
	ft_strdel(&state);
	ft_strdel(&command);
}

static void		print_joblist(uint8_t flag)
{
	char		*state;
	char		*avs;
	t_list		*job_ptr;
	t_job		*job;

	job_ptr = g_shell->job_list;
	while (job_ptr != NULL)
	{
		avs = NULL;
		state = NULL;
		job = ((t_job*)job_ptr->data);
		state_to_str(job, &state);
		get_job_av(job, &avs);
		if (flag & JOBCTL_LONG)
			print_longformat(job, state);
		else if (flag & JOBCTL_ID)
			ft_printf("%d\n", job->pgid);
		else
			ft_printf("[%d]%c %s \t %s\n", job->id, job->current,
							state, avs);
		ft_strdel(&state);
		ft_strdel(&avs);
		job_ptr = job_ptr->next;
	}
}

void			print_jobs(t_job *job, uint8_t flag)
{
	update_jobinfos(g_shell);
	if (job == NULL)
		print_joblist(flag);
	else
		print_jobinfo(job, flag);
	remove_done_jobs(g_shell);
}
