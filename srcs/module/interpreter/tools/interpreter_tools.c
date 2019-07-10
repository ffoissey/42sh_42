/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 10:30:03 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <fcntl.h>

int			get_failed_process(void *data, void *context)
{
	t_process		*current;
	uint16_t		errors;

	(void)context;
	current = data;
	errors = (IS_EXP_ERROR | IS_OPEN_FAILED
			| IS_CRITICAL | IS_DUP_FAILED | IS_ASSIGN);
	if ((current->type & ~(IS_ALONE)) & errors)
		return (TRUE);
	return (FALSE);
}

void		re_open_std(const uint8_t std, char *tty_name)
{
	int		fd;

	fd = open(tty_name, O_RDWR);
	if (std & CLOSED_STDIN)
		dup2(fd, STDIN_FILENO);
	if (std & CLOSED_STDOUT)
		dup2(fd, STDOUT_FILENO);
	if (std & CLOSED_STDERR)
		dup2(fd, STDERR_FILENO);
	if (fd >= 3)
		close(fd);
	return ;
}

uint8_t		check_job(t_job *job, int job_type)
{
	char	*last_status;
	char	*last_job;

	last_job = ft_itoa(job->type);
	add_var(&g_shell->intern, "job_type", last_job, READONLY_VAR);
	ft_strdel(&last_job);
	last_status = get_var(g_shell->intern, "?");
	if (job->state & KILLED)
		return (FALSE);
	else if (job_type & GROUP_AND)
	{
		if (ft_strequ(last_status, "0") == FALSE)
			return (FALSE);
	}
	else if (job_type & GROUP_OR)
	{
		if (ft_strequ(last_status, "0") == TRUE)
			return (FALSE);
	}
	return (TRUE);
}

void		set_stopped(void *data)
{
	t_process	*process;

	process = data;
	process->stopped = TRUE;
	return ;
}

int			set_signaled(void *context, void *data)
{
	t_job		*job;
	uint32_t	*signo;

	job = data;
	signo = context;
	job->state |= KILLED;
	job->signo = *signo;
	ft_lstiter(job->processes, set_stopped);
	return (0);
}
