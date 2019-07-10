/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_lexer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 08:16:54 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int	end_parameter(t_parameter *param)
{
	if (param->source[param->index] == '\0')
		return (TRUE);
	if (ft_strlen(param->buffer->buffer) == 0)
	{
		if (ft_strchr(PEX_SPECIAL, param->source[param->index]))
		{
			vct_add(param->buffer, param->source[param->index]);
			param->index++;
			return (TRUE);
		}
		else if (!ft_isalpha(param->source[param->index])
				&& param->source[param->index] != '#')
			return (TRUE);
	}
	else if (ft_strchr(PEX_PARAM_INTERUPT, param->source[param->index]))
		return (TRUE);
	return (FALSE);
}

static void	pex_parameter(t_parameter *param)
{
	if (end_parameter(param) == TRUE)
	{
		generate_pex_token(param);
		if (param->source[param->index] == '}')
			param->state = PEX_END;
		else
			param->state = PEX_DELIM;
	}
	else
	{
		vct_add(param->buffer, param->source[param->index]);
		param->index++;
	}
}

static void	pex_delimiter(t_parameter *param)
{
	if (ft_strlen(param->buffer->buffer) == 2
			|| ft_strchr(PEX_VALID_DELIM, param->source[param->index]) == NULL)
	{
		generate_pex_token(param);
		if (param->source[param->index] == '}')
			param->state = PEX_END;
		else
			param->state = PEX_WORD;
	}
	else
	{
		vct_add(param->buffer, param->source[param->index]);
		param->index++;
	}
}

void		generate_pex_token(t_parameter *param)
{
	t_list			*node;
	t_pex_token		token;
	char			*str;

	ft_bzero(&token, sizeof(t_pex_token));
	token.type = param->state;
	str = vct_get_string(param->buffer);
	if (!str || *str == '\0')
		token.data = NULL;
	else
		token.data = ft_strdup(vct_get_string(param->buffer));
	node = ft_lstnew(&token, sizeof(t_pex_token));
	ft_lstaddback(&param->tokens, node);
	vct_del(&param->buffer);
	param->buffer = vct_new(DEFAULT_PEX_BUFFER);
}

void		parameter_lexer(t_parameter *parameter)
{
	static t_paramexp	state[PEX_STATES];

	if (state[0] == NULL)
	{
		state[PEX_PARAM] = pex_parameter;
		state[PEX_DELIM] = pex_delimiter;
		state[PEX_WORD] = pex_word;
	}
	while (parameter->state != PEX_END)
	{
		if (parameter->source[parameter->index] == '\0')
		{
			parameter_print_debug(parameter->tokens);
			return ;
		}
		state[parameter->state](parameter);
	}
	parameter_print_debug(parameter->tokens);
}
