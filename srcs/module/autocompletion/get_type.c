/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:21:42 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

enum e_result_type			is_file_type(char *input, size_t len)
{
	while (len > 0 && (input[len - 1] == ' ' || input[len - 1] == '\t'))
		len--;
	if (len == 0 || is_cmd_delimiter(input[len - 1]) == TRUE)
		return (CMD_TYPE);
	return (FILE_TYPE);
}

static enum e_result_type	process_get_result_type(char *input, size_t len)
{
	if (len == 0 || is_cmd_delimiter(input[len - 1]) == TRUE)
		return (CMD_TYPE);
	if (input[len - 1] == ' ' || input[len - 1] == '\t'
			|| input[len - 1] == '}' || input[len - 1] == '/'
			|| input[len - 1] == '>' || input[len - 1] == '<')
		return (is_file_type(input, len));
	if (input[len - 1] == '$')
		return (VARIABLE_TYPE);
	if (input[len - 1] == '{')
	{
		if (process_get_result_type(input, --len) == VARIABLE_TYPE)
			return (VARIABLE_BRACKET_TYPE);
	}
	return (process_get_result_type(input, len - 1));
}

enum e_result_type			get_result_type(char *input)
{
	size_t		len;

	len = input == NULL ? 0 : ft_strlen(input);
	if (len == 0)
		return (CMD_TYPE);
	if (ft_strequ(".", input) == TRUE)
		return (FILE_TYPE);
	return (process_get_result_type(input, len));
}
