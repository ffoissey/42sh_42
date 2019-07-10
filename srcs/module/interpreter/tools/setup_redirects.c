/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 13:44:25 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int	set_redirect(void *context, void *data)
{
	static t_redirection	*redirecter;
	t_action				*action;
	t_redirect				redirect;

	(void)context;
	if (redirecter == NULL)
		redirecter = redirecter_init();
	action = data;
	ft_bzero(&redirect, sizeof(t_redirect));
	if ((*redirecter)[action->type](&redirect, action) == FAILURE)
		return (FAILURE);
	if (do_redirect(&redirect) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int			setup_redirect(t_process *proc)
{
	if (ft_lstiter_ctx(proc->redirects, proc, set_redirect) == FAILURE)
	{
		ft_lstdel(&proc->redirects, del_action);
		return (FAILURE);
	}
	return (SUCCESS);
}
