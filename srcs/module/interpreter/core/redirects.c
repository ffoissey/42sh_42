/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 10:33:09 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

int		check_redirect_error(void *context, void *data)
{
	t_process		*process;
	t_redirect		*redirect;

	process = context;
	redirect = data;
	if (redirect->type & FD_OPEN_ERROR)
		process->type = IS_OPEN_FAILED;
	if (redirect->type & FD_DUP_ERROR)
		process->type = IS_DUP_FAILED;
	if (redirect->type & FD_CRITICAL_ERROR)
	{
		ft_dprintf(2, "42sh: [CRITICAL] Malloc error\n");
		process->type = IS_CRITICAL;
	}
	if (redirect->type & FD_BAD_DESCRIPTOR)
	{
		ft_dprintf(2, "42sh: %d: bad file descriptor\n", redirect->to);
		process->type = IS_DUP_FAILED;
	}
	if (redirect->type & FD_AMBIGOUS_REDIRECT)
		process->type = IS_DUP_FAILED;
	if (process->type & (IS_DUP_FAILED | IS_CRITICAL | IS_OPEN_FAILED))
		return (FAILURE);
	return (SUCCESS);
}

void	set_ambigous_redirect(t_redirect *redirect, t_list *node)
{
	t_token		*token;

	token = node->data;
	ft_dprintf(2, "42sh: %s: ambigous_redirect\n", token->data);
	redirect->type = FD_AMBIGOUS_REDIRECT;
}

int		redirect_or_other(void *context, void *data)
{
	t_action		*action;

	(void)context;
	action = data;
	if (action->type == A_ASSIGN)
		return (FALSE);
	return (TRUE);
}

void	close_redirect(void *data)
{
	t_token	*token;
	int		fd;

	token = data;
	fd = ft_atoi(token->data);
	if (fd >= 3)
		close(fd);
}

void	del_process_redirect(void *data)
{
	t_process	*process;

	process = data;
	ft_lstiter(process->redirects, del_action);
}
