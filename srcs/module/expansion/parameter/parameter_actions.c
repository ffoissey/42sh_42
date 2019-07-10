/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_actions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 02:46:51 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			default_expansion(t_list *intern, t_parameter *param, int mode)
{
	t_pex_token	*parameter;
	t_pex_token	*word;
	char		*data;
	int			status;

	parameter = param->tokens->data;
	word = mode & EXPANDED_PARAM ? param->tokens->next->next->data : NULL;
	status = get_var_status(intern, parameter->data);
	if (status < 0)
		param->expanded = ft_strdup(word ? word->data : "");
	else if ((data = get_var(intern, parameter->data)) == NULL)
	{
		if (param->modifier & COLON_ON && status & SET_VAR)
			param->expanded = ft_strdup(word ? word->data : "");
		else
			param->expanded = ft_strdup("");
	}
	else
		param->expanded = ft_strdup(data);
	return (0);
}

int			assign_expansion(t_list *intern, t_parameter *param, int mode)
{
	t_pex_token	*word;
	char		*data;
	int			status;
	char		*parameter;

	word = mode & EXPANDED_PARAM ? param->tokens->next->next->data : NULL;
	parameter = ((t_pex_token *)param->tokens->data)->data;
	if ((status = get_var_status(intern, parameter)) < 0)
	{
		add_var(&intern, parameter, word ? word->data : "", SET_VAR);
		param->expanded = ft_strdup(word ? word->data : "");
	}
	else if ((data = get_var(intern, param->tokens->data)) == NULL)
	{
		if (param->modifier & COLON_ON && status & SET_VAR)
		{
			add_var(&intern, parameter, word ? word->data : "", SET_VAR);
			param->expanded = ft_strdup(word == NULL ? "" : word->data);
		}
		else
			param->expanded = ft_strdup("");
	}
	else
		param->expanded = ft_strdup(data);
	return (0);
}

static int	error_exists(char *parameter, char *message)
{
	if (message == NULL)
		ft_dprintf(2, "42sh: %s: %s\n", parameter, PEX_NULL_DEFAULT);
	else
		ft_dprintf(2, "42sh: %s: %s\n", parameter, message);
	return (-1);
}

int			exists_expansion(t_list *intern, t_parameter *param, int mode)
{
	t_pex_token	*parameter;
	t_pex_token	*word;
	char		*data;
	int			status;

	parameter = param->tokens->data;
	word = mode & EXPANDED_PARAM ? param->tokens->next->next->data : NULL;
	status = get_var_status(intern, parameter->data);
	if (status < 0)
		return (error_exists(parameter->data, word ? word->data : NULL));
	else if ((data = get_var(intern, parameter->data)) == NULL)
	{
		if (param->modifier & COLON_ON && status & SET_VAR)
			return (error_exists(parameter->data, word ? word->data : NULL));
		else
			param->expanded = ft_strdup("");
	}
	else
		param->expanded = ft_strdup(data);
	return (0);
}

int			replace_expansion(t_list *intern, t_parameter *param, int mode)
{
	t_pex_token	*parameter;
	t_pex_token	*word;
	char		*data;
	int			status;

	parameter = param->tokens->data;
	word = mode & EXPANDED_PARAM ? param->tokens->next->next->data : NULL;
	status = get_var_status(intern, parameter->data);
	if (status < 0)
		param->expanded = ft_strdup("");
	else if (status > 0 && (data = get_var(intern, parameter->data)) == NULL)
	{
		if (param->modifier & COLON_ON && status & SET_VAR)
			param->expanded = ft_strdup(word ? word->data : "");
		else
			param->expanded = ft_strdup("");
	}
	else
		param->expanded = ft_strdup(word ? word->data : "");
	return (0);
}
