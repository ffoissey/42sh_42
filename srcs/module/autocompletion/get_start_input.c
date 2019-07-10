/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_start_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:21:32 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static char	*get_start_input_file(char *input, size_t len)
{
	while (len > 0)
	{
		if (input[len] == ' ' || input[len] == '\t'
			|| input[len] == '}'
			|| input[len] == '>' || input[len] == '<')
			return (input + len + 1);
		len--;
	}
	if (input[0] == '/' || input[0] == '.')
		return (input);
	return (input + 1);
}

static char	*get_start_input_variable(char *input, size_t len, char c)
{
	while (len > 0)
	{
		if (input[len] == c)
			return (input + len + 1);
		len--;
	}
	return (input + 1);
}

static char	*get_start_input_cmd(char *input, size_t len)
{
	while (len > 0)
	{
		if (is_cmd_delimiter(*input) == TRUE
			|| input[len] == ' ' || input[len] == '\t'
				|| input[len] == '>' || input[len] == '<')
			return (input + len + 1);
		len--;
	}
	return (input);
}

char		*get_start_input(char *input, enum e_result_type type)
{
	size_t	last_char_pos;
	size_t	len;

	if (input == NULL)
		return (NULL);
	len = ft_strlen(input);
	if (len <= 0)
		return (input);
	last_char_pos = len - 1;
	if (type == CMD_TYPE)
		return (get_start_input_cmd(input, last_char_pos));
	else if (type == VARIABLE_TYPE)
		return (get_start_input_variable(input, last_char_pos, '$'));
	else if (type == VARIABLE_BRACKET_TYPE)
		return (get_start_input_variable(input, last_char_pos, '$') + 1);
	return (get_start_input_file(input, last_char_pos));
}
