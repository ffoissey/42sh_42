/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_get.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 00:09:52 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		single_parameter(t_list *intern, t_parameter *parameter)
{
	t_pex_token	*token;
	char		*data;

	token = parameter->tokens->data;
	if (token->data)
	{
		if (token->data[0] == '#')
		{
			if ((data = get_var(intern, token->data + 1)) == NULL)
				parameter->expanded = ft_strdup("0");
			else
				ft_asprintf(&parameter->expanded, "%d", ft_strlen(data));
		}
		else
		{
			if ((data = get_var(intern, token->data)) == NULL)
				parameter->expanded = ft_strdup("");
			else
				parameter->expanded = ft_strdup(data);
		}
		return (0);
	}
	ft_dprintf(2, "42sh: bad substitution\n");
	return (-1);
}

void	init_advanced_pex(t_advanced_pex expansion[PEX_ADVANCED_EXP])
{
	expansion[0] = default_expansion;
	expansion[1] = assign_expansion;
	expansion[2] = exists_expansion;
	expansion[3] = replace_expansion;
	expansion[4] = suffix_expansion;
	expansion[5] = prefix_expansion;
}

int		advanced_expansion(t_list *intern, t_parameter *parameter)
{
	static t_advanced_pex	expansion[PEX_ADVANCED_EXP];
	int						delim;
	t_pex_token				*param;

	if (expansion[0] == NULL)
		init_advanced_pex(expansion);
	param = parameter->tokens->data;
	delim = get_delimiter(parameter, parameter->tokens->next->data);
	if (delim < 0 || param->data[0] == '#')
	{
		ft_dprintf(2, "42sh: %s: bad substitution\n", parameter->source);
		return (-1);
	}
	else
		return (expansion[delim](intern, parameter, EXPANDED_PARAM));
}

int		double_parameter(t_list *intern, t_parameter *parameter)
{
	static t_advanced_pex	expansion[PEX_ADVANCED_EXP];
	int						delim;
	t_pex_token				*param;

	if (expansion[0] == NULL)
		init_advanced_pex(expansion);
	param = parameter->tokens->data;
	delim = get_delimiter(parameter, parameter->tokens->next->data);
	if (delim < 0 || param->data[0] == '#')
	{
		ft_dprintf(2, "42sh: %s: bad substitution\n", parameter->source);
		return (-1);
	}
	else
		return (expansion[delim](intern, parameter, EMPTY_PARAM));
}

int		parameter_get(t_list *intern, t_parameter *parameter)
{
	if (ft_lstlen(parameter->tokens) == 1)
		return (single_parameter(intern, parameter));
	else if (ft_lstlen(parameter->tokens) == 2)
		return (double_parameter(intern, parameter));
	else if (ft_lstlen(parameter->tokens) == 3)
		return (advanced_expansion(intern, parameter));
	return (-1);
}
