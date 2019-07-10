/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 17:37:26 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t		interpreter(t_registry *shell, t_list **cmd_group)
{
	t_list		*job_lst;
	char		*input;

	ptr_to_job_lst(&job_lst, SET_ADDR);
	job_lst = ft_lstmap(*cmd_group, shell, group_to_job, del_group);
	ft_lstdel(cmd_group, del_group);
	if ((shell->option.option & RECORD_HISTORY_OPT)
			&& (input = get_var(g_shell->intern, "_input")) != NULL)
		history(g_shell, input, ADD_ENTRY);
	load_signal_profile(EXEC_PROFILE);
	ft_lstiter_ctx(job_lst, shell, run_job);
	add_var(&shell->intern, "job_type", "0", READONLY_VAR);
	ft_lstdel(&job_lst, del_job);
	shell->sigint = 0;
	ptr_to_job_lst(NULL, SET_ADDR);
	return (SUCCESS);
}
