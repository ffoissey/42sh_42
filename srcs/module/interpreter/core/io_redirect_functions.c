/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirect_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 17:41:01 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <fcntl.h>

int	duplicate_fd(t_redirect *redirect, t_action *action)
{
	t_token		*token;

	token = action->data->data;
	redirect->from = ft_atoi(token->data);
	redirect->to = get_io_noprotect(action->data->next);
	redirect->type = FD_DUP;
	return (SUCCESS);
}

int	io_append(t_redirect *redirect, t_action *action)
{
	char		*filename;
	int			open_flags;
	int			return_value;
	int			fd;

	return_value = SUCCESS;
	filename = get_filename(action->data);
	if (filename == NULL)
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
	{
		open_flags = O_RDWR | O_APPEND | O_CREAT | O_CLOEXEC;
		fd = get_io_noprotect(action->data->next);
		return_value = open_write_file(redirect, filename, open_flags, fd);
	}
	ft_strdel(&filename);
	return (return_value);
}

int	io_truncate(t_redirect *redirect, t_action *action)
{
	char		*filename;
	int			open_flags;
	int			return_value;
	int			fd;

	filename = get_filename(action->data);
	return_value = SUCCESS;
	if (filename == NULL)
	{
		redirect->type |= FD_CRITICAL_ERROR;
		return_value = FAILURE;
	}
	else if (*filename == '\0')
	{
		set_ambigous_redirect(redirect, action->data);
		return_value = FAILURE;
	}
	else
	{
		open_flags = O_RDWR | O_TRUNC | O_CREAT;
		fd = get_io_noprotect(action->data->next);
		return_value = open_write_file(redirect, filename, open_flags, fd);
	}
	ft_strdel(&filename);
	return (return_value);
}

int	io_readfile(t_redirect *redirect, t_action *action)
{
	char		*filename;
	int			open_flag;
	int			return_value;
	int			fd;

	filename = get_filename(action->data);
	return_value = 0;
	open_flag = O_RDONLY | O_CLOEXEC;
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
	{
		fd = get_io(action->data->next);
		return_value = open_read_file(redirect, filename, open_flag, fd);
	}
	ft_strdel(&filename);
	return (return_value);
}

int	io_readfd(t_redirect *redirect, t_action *action)
{
	int		action_type_value;
	char	*str;
	int		return_value;

	str = NULL;
	return_value = 0;
	action_type_value = get_custom_fd(&str, action->data);
	if (action_type_value == FAILURE)
		redirect->type = FD_CRITICAL_ERROR;
	else if (action_type_value == -2)
	{
		redirect->type = FD_AMBIGOUS_REDIRECT;
		return_value = FAILURE;
	}
	else
		return_value = action_type(redirect, action_type_value, str);
	ft_strdel(&str);
	return (return_value);
}
