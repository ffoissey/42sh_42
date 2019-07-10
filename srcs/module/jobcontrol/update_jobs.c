/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_jobs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 10:07:40 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		update_current_job(t_registry *shell)
{
	t_list *jobs;

	jobs = shell->job_list;
	while (jobs != NULL)
	{
		if (g_shell->current_plus == jobs)
			((t_job*)jobs->data)->current = '+';
		else if (g_shell->current_minus == jobs)
			((t_job*)jobs->data)->current = '-';
		else
			((t_job*)jobs->data)->current = ' ';
		jobs = jobs->next;
	}
}

static void		update_job_ids(t_registry *shell)
{
	uint32_t	id;
	t_job		*job;
	t_list		*job_ptr;

	id = 1;
	job_ptr = shell->job_list;
	while (id <= shell->active_jobs && job_ptr != NULL)
	{
		job = job_ptr->data;
		job->id = id;
		++id;
		job_ptr = job_ptr->next;
	}
}

void			update_jobinfos(t_registry *shell)
{
	mark_proc_status();
	update_job_ids(shell);
	update_current_job(shell);
}
