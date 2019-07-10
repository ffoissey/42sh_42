/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobctl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:17:58 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_list				*remove_job_from_list(t_list **list, t_job *job)
{
	t_list	*ptr;
	t_list	*job_ptr;

	if (job == NULL || *list == NULL)
		return (NULL);
	job_ptr = *list;
	while (job_ptr != NULL && (t_job*)job_ptr->data != job)
		job_ptr = job_ptr->next;
	if (job_ptr == *list)
		return (get_job_ptr(list, job_ptr));
	else
	{
		ptr = *list;
		while (ptr->next != NULL && ptr->next != job_ptr)
			ptr = ptr->next;
		if (ptr->next != NULL)
		{
			job_ptr = (ptr->next);
			ptr->next = ptr->next->next;
			return (job_ptr);
		}
	}
	return (NULL);
}

static void			job_to_registry(t_registry *shell, t_job *job)
{
	char		*avs;
	t_list		*data;
	t_job		job_cpy;

	avs = NULL;
	ft_bzero(&job_cpy, sizeof(t_job));
	job->state = STOPPED;
	mark_job_as_stopped(job);
	ft_memcpy(&job_cpy, job, sizeof(t_job));
	get_job_av(job, &avs);
	ft_printf("[%d]+  Stopped(%d) \t %s\n", job->id, job->signo, avs);
	ft_strdel(&avs);
	job->processes = NULL;
	job->term_modes = NULL;
	data = ft_lstnew(&job_cpy, sizeof(t_job));
	ft_lstaddback(&shell->job_list, data);
	push_current_job(shell, data);
}

void				job_to_foreground(t_registry *shell, t_job *job)
{
	char	*avs;
	t_list	*todel;

	if (job == NULL || !(job->processes != NULL))
		return ;
	mark_proc_status();
	if (job_is_completed(job) == TRUE)
	{
		job_already_done(shell, job);
		return ;
	}
	mark_job_as_running(job);
	todel = remove_job_from_list(&shell->job_list, job);
	shell->active_jobs--;
	update_jobinfos(shell);
	pop_current_job(shell, job);
	get_job_av(job, &avs);
	ft_printf("%s\n", avs);
	ft_strdel(&avs);
	tcsetpgrp(STDIN_FILENO, job->pgid);
	killpg(job->pgid, SIGCONT);
	waiter(job);
	del_job(job);
	free(job);
	free(todel);
}

void				job_run_background(t_registry *shell, t_job *job)
{
	(void)shell;
	job->state = RUNNING;
	job->signo = SIGCONT;
	killpg(job->pgid, SIGCONT);
	tcsetpgrp(STDIN_FILENO, shell->pid);
	term_mode(TERMMODE_EXEC);
}

void				jobctl(t_registry *shell, t_job *job, uint8_t flag)
{
	if (jobctl_is_active(shell) == FALSE)
		return ;
	if (flag & JOBCTL_LIST)
		print_jobs(job, flag);
	else if (flag & JOBCTL_PUTINBG)
		job_to_registry(shell, job);
	else if (flag & JOBCTL_PUTINFG)
		job_to_foreground(shell, job);
	else if (flag & JOBCTL_RUNINBG)
		job_run_background(shell, job);
}
