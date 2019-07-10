/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 08:31:52 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int	parameter_check(t_pex_token *token)
{
	if (token->data == NULL)
	{
		ft_dprintf(2, "42sh: bad substitution\n");
		return (-1);
	}
	if (ft_strequ(token->data, "0"))
		return (0);
	if (ft_isdigit(token->data[0]))
		return (-1);
	return (0);
}

static int	word_check(t_list *intern, t_pex_token *token)
{
	char	*expanded;

	if ((expanded = expansion_word(intern, token->data)) == NULL)
		return (-1);
	ft_strdel(&token->data);
	token->data = expanded;
	return (0);
}

void		init_delimiters(char *delimiters[PEX_DELIMITERS])
{
	delimiters[0] = "-";
	delimiters[1] = "=";
	delimiters[2] = "?";
	delimiters[3] = "+";
	delimiters[4] = "%";
	delimiters[5] = "#";
	delimiters[6] = ":-";
	delimiters[7] = ":=";
	delimiters[8] = ":?";
	delimiters[9] = ":+";
	delimiters[10] = "%%";
	delimiters[11] = "##";
}

int			get_delimiter(t_parameter *param, t_pex_token *token)
{
	static char	*delimiters[PEX_DELIMITERS];
	int			index;

	if (delimiters[0] == NULL)
		init_delimiters(delimiters);
	index = 0;
	while (index < PEX_DELIMITERS)
	{
		if (ft_strequ(token->data, delimiters[index]))
		{
			if (token->data[0] == ':')
				param->modifier |= COLON_ON;
			else if (token->data[1] == '%' || token->data[1] == '#')
				param->modifier |= LONGEST_ON;
			return (index >= 6 ? index - 6 : index);
		}
		index++;
	}
	ft_dprintf(2, "42sh: bad substitution\n");
	return (-1);
}

int			parameter_parse(t_list *intern, t_parameter *parameter)
{
	t_list		*tokens;
	int			result;

	tokens = parameter->tokens;
	if (!tokens)
		return (-1);
	if ((result = parameter_check(tokens->data)) == -1)
		return (result);
	if (tokens->next == NULL)
		return (0);
	if ((result = get_delimiter(parameter, tokens->next->data)) == -1)
		return (result);
	if (tokens->next->next == NULL)
		return (0);
	if ((result = word_check(intern, tokens->next->next->data)) == -1)
		return (result);
	return (0);
}
