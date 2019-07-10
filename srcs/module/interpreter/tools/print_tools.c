/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 10:30:55 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	print_signaled(char *command, int signo)
{
	static char			*signal_string[16] = { NULL, "terminal hangup", NULL
											, "Quit"
											, "Illegal instruction", "Trap"
											, "Abort", "EMT Trap"
											, "Floating point exception"
											, "killed", "bus error"
											, "segmentation fault"
											, "Bad system call"
											, NULL
											, "Alarm clock"
											, "Terminated"};

	if (signo != 2 && signo != 13 && signo >= 1 && signo <= 15)
		ft_dprintf(2, "\n42sh: %.*s: %s [%d]\n"
			, ft_strlen(command) - 1, command, signal_string[signo], signo);
}

void	print_var_lst(void *data)
{
	t_variable *var;

	var = data;
	ft_printf("\x1b[33mVar = %s || Data = %s\n\x1b[0m", var->name, var->data);
}

void	print_process(void *data)
{
	t_process *process;

	process = data;
	ft_showtab(process->av);
	ft_putstr("\x1b[33m");
	ft_printf("process->type: %d | process->pid: %d | process->pgid: %d\n"
			, process->type, process->pid, *process->pgid);
	ft_putstr("\x1b[0m");
}

void	print_job(void *data)
{
	t_job *job;

	job = data;
	ft_printf("\x1b[33mpgid : %ld | job_type: %u\n\x1b[0m"
			, job->pgid
			, job->type);
}
