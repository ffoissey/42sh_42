/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_avs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 14:58:39 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		get_job_av(t_job *job, char **str)
{
	uint32_t	avnb;
	t_list		*process;
	t_process	*proc_ptr;

	*str = ft_strnew(2048);
	process = job->processes;
	while (process != NULL)
	{
		avnb = 0;
		proc_ptr = ((t_process*)process->data);
		while (proc_ptr->av[avnb] != NULL)
		{
			ft_strcat(*str, " ");
			ft_strcat(*str, proc_ptr->av[avnb]);
			++avnb;
		}
		process = process->next;
		if (process != NULL)
			ft_strcat(*str, " |");
	}
}

void		get_process_av(t_process *process, char **str)
{
	uint32_t	avnb;

	avnb = 0;
	*str = ft_strnew(256);
	while (process->av[avnb] != NULL)
	{
		ft_strcat(*str, " ");
		ft_strcat(*str, process->av[avnb]);
		++avnb;
	}
}
