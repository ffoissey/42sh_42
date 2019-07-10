/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 16:03:30 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_option			get_option_jobs(char *s, t_option option)
{
	option = 0;
	while (*s)
	{
		if (*s == 'l')
			option |= L_OPT;
		else if (*s == 'p')
			option |= P_OPT;
		else
		{
			ft_dprintf(STDERR_FILENO,
					"42sh: jobs: -%c: invalid option\n", *s);
			ft_dprintf(STDERR_FILENO, "jobs: usage: jobs [-l|-p] [%%job_id]\n");
			return (ERROR_OPT);
		}
		s++;
	}
	return (option);
}

static void			jobs(t_job *job, t_option option)
{
	if (option & L_OPT)
		jobctl(g_shell, job, JOBCTL_LIST | JOBCTL_LONG);
	else if (option & P_OPT)
		jobctl(g_shell, job, JOBCTL_LIST | JOBCTL_ID);
	else
		jobctl(g_shell, job, JOBCTL_LIST);
}

static uint8_t		get_jobname(char **av, t_option option)
{
	uint8_t		ret;
	int8_t		result;
	t_job		*job;

	ret = SUCCESS;
	while (*av != NULL)
	{
		result = parse_jobid(&job, *av);
		if (result == FAILURE || result == BAD_PERCENTAGE)
		{
			if (result == FAILURE)
				ft_dprintf(2, "jobs: %s: no such job.\n", *av);
			else
				ft_dprintf(2, "jobs: usage: jobs [-l|-p] [%%jobID]\n");
			ret = 1;
			++av;
			continue ;
		}
		jobs(job, option);
		++av;
	}
	return (ret);
}

int8_t				jobs_blt(t_list *intern, char **av)
{
	t_option	option;
	uint8_t		ret;

	(void)intern;
	if (jobctl_is_active(g_shell) == FALSE)
		return (FAILURE);
	++av;
	if ((option = set_options(&av, get_option_jobs)) == ERROR_OPT)
		return (2);
	ret = SUCCESS;
	if (*av == NULL)
		jobs(NULL, option);
	else
		ret = get_jobname(av, option);
	return (ret);
}
