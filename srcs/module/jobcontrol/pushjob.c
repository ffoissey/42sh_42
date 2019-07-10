/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushjob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:59:23 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			push_current_job(t_registry *shell, t_list *job)
{
	char	*pgid;

	shell->current_minus = shell->current_plus;
	shell->current_plus = job;
	pgid = ft_itoa(((t_job*)job->data)->pgid);
	add_var(&shell->intern, "!", pgid, READONLY_VAR);
	ft_strdel(&pgid);
}

static void		set_minus(t_registry *shell, t_list *jobs)
{
	jobs = shell->job_list;
	shell->current_minus = NULL;
	while (jobs != NULL)
	{
		if (jobs != shell->current_plus && jobs != NULL)
			shell->current_minus = jobs;
		jobs = jobs->next;
	}
}

static void		set_plus(t_registry *shell)
{
	if (shell->current_minus == NULL)
	{
		shell->current_plus->data = NULL;
		shell->current_plus = NULL;
	}
	else
		shell->current_plus = shell->current_minus;
}

void			pop_current_job(t_registry *shell, t_job *job)
{
	t_list	*jobs;

	jobs = NULL;
	if (shell->job_list == NULL)
	{
		shell->current_minus = NULL;
		shell->current_plus = NULL;
		return ;
	}
	if (job == NULL || shell->current_plus == NULL
		|| shell->current_minus == NULL)
		return ;
	if (((t_job*)shell->current_plus->data) == job)
	{
		set_plus(shell);
		jobs = shell->job_list;
		while (jobs != NULL)
		{
			if (jobs != shell->current_plus && jobs != NULL)
				shell->current_minus = jobs;
			jobs = jobs->next;
		}
	}
	else if (((t_job*)shell->current_minus->data) == job)
		set_minus(shell, jobs);
}
