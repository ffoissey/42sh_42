/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_redirect_functions.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 20:23:24 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <fcntl.h>

static int	get_filename_special(t_list *node, char **file)
{
	int			action_type;
	t_token		*token;
	char		*filename;

	token = node->data;
	if ((filename = expansion_pipeline(g_shell->intern, token->data)) == NULL)
		return (FAILURE);
	*file = filename;
	if ((action_type = define_io_dup_move(token)) != A_AMBIGOUS_REDIRECT)
		return (action_type);
	return (SUCCESS);
}

static int	set_filename_special(t_redirect *redirect, char *filename, int type)
{
	int			test;

	test = 0;
	redirect->to = ft_atoi(filename);
	if (write(redirect->to, &test, 0) == -1)
	{
		if (read(redirect->to, &test, 0) == -1)
		{
			ft_dprintf(2, "42sh: %d: Bad File descriptor\n", redirect->to);
			redirect->type = FD_BAD_DESCRIPTOR;
			return (FAILURE);
		}
	}
	redirect->from = STDOUT_FILENO;
	if (type == A_CLOSE)
		redirect->type = FD_CLOSE_SPECIAL;
	else if (type == A_MOVE)
		redirect->type = FD_MOVE;
	else
		redirect->type = FD_DUP;
	return (SUCCESS);
}

int			stdout_truncate_special(t_redirect *redirect, t_action *action)
{
	char		*filename;
	int			open_flags;
	int			type;
	int			return_value;

	filename = NULL;
	return_value = 0;
	open_flags = O_WRONLY | O_TRUNC | O_CREAT | O_CLOEXEC;
	if ((type = get_filename_special(action->data, &filename)) > 0)
		return_value = set_filename_special(redirect, filename, type);
	else if (type == FAILURE)
	{
		redirect->type = FD_CRITICAL_ERROR;
		return_value = FAILURE;
	}
	else if (*filename == '\0')
	{
		set_ambigous_redirect(redirect, action->data);
		return_value = FAILURE;
	}
	else
		return_value = open_write_file(redirect, filename, open_flags, 1);
	ft_strdel(&filename);
	return (return_value);
}
