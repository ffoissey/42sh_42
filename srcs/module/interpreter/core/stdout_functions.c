/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdout_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 20:28:18 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 17:10:15 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <fcntl.h>

int	check_path_access(t_redirect *redirect, char *filename)
{
	if (access(filename, F_OK) == SUCCESS)
	{
		if (access(filename, W_OK) == FAILURE
				&& access(filename, X_OK) == FAILURE)
		{
			ft_dprintf(2, "42sh: %s: permission denied\n", filename);
			redirect->type = FD_OPEN_ERROR;
			return (FAILURE);
		}
		return (SUCCESS);
	}
	return (-2);
}

int	check_absolute_path(t_redirect *redirect, char *filename)
{
	char	*path;
	char	*holder;
	int		return_value;

	return_value = 0;
	holder = NULL;
	path = ft_strrchr(filename, '/');
	if ((path - filename) == 0)
	{
		ft_dprintf(2, "42sh: %s: permission denied\n", filename);
		redirect->type = FD_OPEN_ERROR;
		return (FAILURE);
	}
	ft_asprintf(&holder, "%.*s", path - filename, filename);
	path = holder;
	if ((return_value = check_path_access(redirect, path)) != SUCCESS)
	{
		if (return_value == -2)
			ft_dprintf(2, "42sh: %s: no such file or directory\n", filename);
		redirect->type = FD_OPEN_ERROR;
		ft_strdel(&holder);
		return (FAILURE);
	}
	ft_strdel(&holder);
	return (SUCCESS);
}

int	open_write_file(t_redirect *redirect, char *filename, int flag, int from)
{
	if (redirect->from == FAILURE)
	{
		redirect->type = FD_BAD_DESCRIPTOR;
		ft_dprintf(2, "42sh: %d: Bad File descriptor\n", filename);
		return (FAILURE);
	}
	if (filename[0] == '/' && check_absolute_path(redirect, filename))
		return (FAILURE);
	else if (check_path_access(redirect, filename) == FAILURE)
		return (FAILURE);
	if ((redirect->to = open(filename, flag, 0644)) == -1)
	{
		ft_dprintf(2, "42sh: %s: no such file or directory\n", filename);
		redirect->type = FD_OPEN_ERROR;
		return (FAILURE);
	}
	else
		redirect->type = FD_REDIRECT;
	redirect->from = from;
	return (SUCCESS);
}

int	stdout_append(t_redirect *redirect, t_action *action)
{
	char		*filename;
	int			open_flags;
	int			return_value;

	filename = get_filename(action->data);
	open_flags = O_WRONLY | O_APPEND | O_CREAT | O_CLOEXEC;
	if (filename == NULL)
	{
		redirect->type = FD_CRITICAL_ERROR;
		return (FAILURE);
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

int	stdout_truncate(t_redirect *redirect, t_action *action)
{
	char		*filename;
	int			open_flags;
	int			return_value;

	filename = get_filename(action->data);
	open_flags = O_WRONLY | O_TRUNC | O_CREAT | O_CLOEXEC;
	if (filename == NULL)
	{
		redirect->type = FD_CRITICAL_ERROR;
		return (FAILURE);
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
