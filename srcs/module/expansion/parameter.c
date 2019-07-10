/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 04:51:53 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		parameter_replace(char **dest, int i, t_parameter *param)
{
	t_vector *vector;

	vector = vct_dups(*dest);
	vct_replace_string(vector, i, i + param->index + 1, param->expanded);
	ft_strdel(dest);
	*dest = ft_strdup(vct_get_string(vector));
	vct_del(&vector);
	return (0);
}

void	del_pex_token(void *data)
{
	t_pex_token *token;

	token = data;
	ft_strdel(&token->data);
}

void	delete_parameter(t_parameter *parameter)
{
	vct_del(&parameter->buffer);
	ft_lstdel(&parameter->tokens, del_pex_token);
	ft_strdel(&parameter->expanded);
}

int		error_parameter(char **dest, t_parameter *parameter)
{
	ft_strdel(dest);
	ft_strdel(&parameter->expanded);
	delete_parameter(parameter);
	return (-1);
}

int		parameter_expansion(t_list *intern, char **dest, int i)
{
	t_parameter parameter;

	ft_bzero(&parameter, sizeof(t_parameter));
	parameter.source = *dest + i;
	parameter.index = 2;
	parameter.buffer = vct_new(DEFAULT_PEX_BUFFER);
	parameter_lexer(&parameter);
	if (parameter_parse(intern, &parameter))
		return (error_parameter(dest, &parameter));
	if (parameter_get(intern, &parameter))
		return (error_parameter(dest, &parameter));
	if (parameter_replace(dest, i, &parameter))
		return (error_parameter(dest, &parameter));
	delete_parameter(&parameter);
	return (1);
}
