/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_module_maths.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:34:01 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

uint8_t	is_operator_m(t_lexer *lexer)
{
	size_t	len_op;
	size_t	i;
	int		type;
	char	*current;

	i = 0;
	type = 16;
	current = lexer->input->buffer + lexer->index;
	while (type >= 0)
	{
		len_op = ft_strlen(g_shell->grammar_m[type]);
		if (ft_strnequ(g_shell->grammar_m[type], current, len_op) == TRUE)
		{
			if (lexer->token_mtype != E_M_DEFAULT
					&& lexer->last_token_mtype != E_M_DELIMITER)
				out_lexer_m(lexer);
			while (i++ < len_op)
				add_to_buffer(lexer);
			lexer->token_mtype = type;
			return (TRUE);
		}
		type--;
	}
	return (FALSE);
}

uint8_t	is_input_end_m(t_lexer *lexer)
{
	if (get_input(lexer, CUR_CHAR) == '\0')
	{
		if (lexer->token_mtype != E_M_DEFAULT
				&& lexer->last_token_mtype != E_M_DELIMITER)
			out_lexer_m(lexer);
		lexer->token_mtype = E_M_END;
		return (TRUE);
	}
	return (FALSE);
}

uint8_t	is_number_m(t_lexer *lexer)
{
	if (lexer->token_mtype == E_M_DEFAULT)
	{
		if (ft_isdigit(get_input(lexer, CUR_CHAR)) == TRUE)
		{
			if (get_input(lexer, CUR_CHAR) == '0')
			{
				if (get_input(lexer, NEXT_CHAR) == 'x'
						|| get_input(lexer, NEXT_CHAR) == 'X')
				{
					add_to_buffer(lexer);
					lexer->token_mtype = E_M_NB_HEX;
				}
				else
					lexer->token_mtype = E_M_NB_OCT;
			}
			else
				lexer->token_mtype = E_M_NB_DEC;
			return (TRUE);
		}
	}
	else if (lexer->token_mtype == E_M_NB_DEC
		|| lexer->token_mtype == E_M_NB_OCT
		|| lexer->token_mtype == E_M_NB_HEX)
		return (TRUE);
	return (FALSE);
}

uint8_t	is_delimiter_m(t_lexer *lexer)
{
	uint8_t	ret;

	ret = FALSE;
	if (get_input(lexer, CUR_CHAR) == ' ')
		ret = TRUE;
	else if (get_input(lexer, CUR_CHAR) == '\t')
		ret = TRUE;
	else if (get_input(lexer, CUR_CHAR) == '\n')
		ret = TRUE;
	if (ret == TRUE)
	{
		if (lexer->token_mtype != E_M_DEFAULT)
			out_lexer_m(lexer);
	}
	return (ret);
}
