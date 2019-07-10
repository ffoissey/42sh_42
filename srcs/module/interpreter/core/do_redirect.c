/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 22:06:19 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	pipe_redirection(t_redirect *redirect)
{
	if (redirect->type & FD_PIPE_OUT)
	{
		dup2(redirect->to, STDOUT_FILENO);
		close(redirect->from);
	}
	else
		dup2(redirect->to, STDIN_FILENO);
}

int		dup_redirection(t_redirect *redirect)
{
	if (dup2(redirect->to, redirect->from) == FAILURE)
	{
		ft_dprintf(2, "42sh: %d: Bad file descriptor\n", redirect->to);
		return (FAILURE);
	}
	return (SUCCESS);
}

int		do_redirect(t_redirect *redirect)
{
	if (redirect->type & FD_DUP)
		return (dup_redirection(redirect));
	else if (redirect->type & (FD_MOVE | FD_REDIRECT))
	{
		dup2(redirect->to, redirect->from);
		close(redirect->to);
	}
	else if (redirect->type & FD_CLOSE)
		close(redirect->from);
	else if (redirect->type & FD_CLOSE_SPECIAL)
		close(STDOUT_FILENO);
	return (SUCCESS);
}
