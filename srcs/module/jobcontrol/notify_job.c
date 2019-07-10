/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notify_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:01:47 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_list		*get_job_ptr(t_list **list, t_list *job_ptr)
{
	*list = (job_ptr)->next;
	return (job_ptr);
}

void		job_already_done(t_registry *shell, t_job *job)
{
	t_list	*todel;
	char	*command;

	todel = NULL;
	get_job_av(job, &command);
	ft_printf("[%d]%c %s \t %s\n", job->id, job->current, "Done",
					command);
	ft_strdel(&command);
	ft_dprintf(2, "fg: Job is already done.\n");
	todel = remove_job_from_list(&shell->job_list, job);
	shell->active_jobs--;
	update_jobinfos(shell);
	pop_current_job(shell, job);
	del_job(job);
	free(job);
	free(todel);
	job = NULL;
}

static void	pop_job(t_job *job)
{
	t_list	*todel;

	todel = remove_job_from_list(&g_shell->job_list, job);
	pop_current_job(g_shell, job);
	g_shell->active_jobs--;
	del_job(job);
	free(job);
	free(todel);
	job = NULL;
}

void		notify_job_info(t_list *joblst, char *info)
{
	t_job		*job;
	t_list		*to_del;
	t_list		*jobl;
	char		*command;

	jobl = joblst;
	while (jobl != NULL)
	{
		job = jobl->data;
		if (job != NULL && job_is_completed(job) == TRUE)
		{
			get_job_av(job, &command);
			ft_printf("[%d]%c %s \t %s\n", job->id, job->current, info,
							command);
			ft_strdel(&command);
			to_del = jobl;
			jobl = jobl->next;
			pop_job(job);
			continue ;
		}
		else
			jobl = jobl->next;
	}
	update_jobinfos(g_shell);
}
