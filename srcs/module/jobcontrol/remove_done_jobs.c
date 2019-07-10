/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_done_jobs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:00:09 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	remove_done_jobs(t_registry *shell)
{
	t_job	*job;
	t_list	*job_ptr;
	t_list	*todel;

	job_ptr = shell->job_list;
	while (job_ptr != NULL)
	{
		job = (t_job*)job_ptr->data;
		if (job->state & ENDED)
		{
			todel = remove_job_from_list(&shell->job_list, job);
			free(todel);
		}
		job_ptr = job_ptr->next;
	}
}
