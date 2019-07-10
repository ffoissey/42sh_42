/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:13:40 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		kill_active_jobs(t_registry *shell)
{
	t_list	*job_lst;

	if (shell->job_list == NULL)
		return ;
	job_lst = shell->job_list;
	while (job_lst != NULL)
	{
		kill(((t_job*)job_lst->data)->pgid, SIGKILL);
		job_lst = job_lst->next;
	}
}

static void		free_hash(t_hash hashmap, void (*del)(void *))
{
	ft_hmap_free_content(&hashmap, del);
	free(hashmap.map);
	hashmap.map = NULL;
}

static void		free_registry(t_registry *shell)
{
	ft_strdel(&shell->option.command_str);
	ft_lstdel(&shell->intern, free_node);
	free_hash(shell->hash.bin, free);
	free_hash(shell->hash.blt, NULL);
	free(shell->orig_ios);
	free(shell->exe_ios);
	free(shell->sle_ios);
}

void			close_filedesc(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

void			shell_exit_routine(t_registry *shell, uint8_t ret)
{
	t_list **joblst;

	if (shell->option.option & RECORD_HISTORY_OPT)
	{
		history(shell, NULL, WRITE_HISTFILE);
		history(shell, NULL, RESET_HEAD);
		history(shell, NULL, FREE_HISTORY);
	}
	if (shell->option.option & INTERACTIVE_OPT)
	{
		kill_active_jobs(shell);
		sle(shell, NULL, SLE_EXIT);
	}
	joblst = ptr_to_job_lst(NULL, GET_ADDR);
	if (joblst != NULL && *joblst != NULL)
		ft_lstdel(joblst, del_job);
	term_mode(TERMMODE_DFLT);
	if ((shell->option.option & DEBUG_OPT) != FALSE)
		close(ft_atoi(get_var(shell->intern, INT_DBG_FD)));
	free_registry(shell);
	if (is_shell_interactive(shell) == TRUE && getpid() == shell->pid)
		ft_putendl_fd("exit", STDERR_FILENO);
	close_filedesc();
	exit(ret);
}
