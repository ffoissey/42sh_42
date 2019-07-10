/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_redirect_tools.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 22:36:38 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void	set_context(uint8_t *std, t_redirect *redirect)
{
	if (redirect->from == STDIN_FILENO)
		*std |= CLOSED_STDIN;
	if (redirect->from == STDOUT_FILENO)
		*std |= CLOSED_STDOUT;
	if (redirect->from == STDERR_FILENO)
		*std |= CLOSED_STDERR;
	if (redirect->type == FD_CLOSE_SPECIAL)
	{
		*std |= CLOSED_STDERR;
		*std |= CLOSED_STDOUT;
	}
}

int			builtin_redirect(void *context, void *data)
{
	t_redirect	*redirect;

	redirect = data;
	set_context(context, data);
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
