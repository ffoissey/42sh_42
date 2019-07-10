/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_interface.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:28:28 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**** OUT LEXER PART
*/

static t_token	generate_token(t_lexer *lexer)
{
	t_token	token;

	token.type = lexer->token_type;
	token.data = NULL;
	if (token.type == E_STRING || token.type == E_ASSIGN
			|| token.type == E_IO_NUMBER)
		token.data = ft_strdup(vct_get_string(lexer->buffer));
	return (token);
}

void			out_lexer(t_lexer *lexer)
{
	t_token	token;
	t_list	*node;

	token = generate_token(lexer);
	if ((node = ft_lstnew(&token, sizeof(token))) == NULL)
	{
		ft_strdel(&token.data);
		return ;
	}
	ft_lstaddback(&lexer->tokens, node);
	lexer->state = lexer->token_type == E_END ? L_FINISH : L_PROCESS;
	if (lexer->assignation == LISTEN || lexer->token_type != E_STRING)
		lexer->assignation = POSSIBLE;
	else
		lexer->assignation = IMPOSSIBLE;
	lexer->last_token_type = lexer->token_type;
	lexer->token_type = E_DEFAULT;
	vct_reset(lexer->buffer);
}

/*
**** PROCESS LEXER PART
*/

static uint8_t	is_operator(t_lexer *lexer)
{
	return (token_checker(lexer, START_OPERATOR, END_OPERATOR));
}

static uint8_t	is_inhibitor(t_lexer *lexer)
{
	if (get_input(lexer, CUR_CHAR) == '\\')
		add_to_buffer(lexer);
	else if (get_input(lexer, CUR_CHAR) == '\'')
		loop_quote(lexer);
	else if (get_input(lexer, CUR_CHAR) == '\"')
		loop_dbquote(lexer);
	else if (get_input(lexer, CUR_CHAR) == '$'
			&& get_input(lexer, NEXT_CHAR) == '{')
		loop_braceparam(lexer);
	else if (get_input(lexer, CUR_CHAR) == '$'
		&& get_input(lexer, NEXT_CHAR) == '('
		&& get_input(lexer, NEXT_NEXT_CHAR) == '(')
		loop_maths(lexer);
	else
		return (FALSE);
	if (get_input(lexer, CUR_CHAR) != '\0')
		add_to_buffer(lexer);
	return (TRUE);
}

void			process_lexer(t_lexer *lexer)
{
	if (is_input_end(lexer) == TRUE)
		lexer->state = L_OUT;
	else if (is_inhibitor(lexer) == TRUE)
		lexer->token_type = E_STRING;
	else if (is_io_number(lexer) == TRUE)
		lexer->state = L_OUT;
	else if (is_delimiter(lexer) == TRUE)
		lexer->index++;
	else if (is_operator(lexer) == TRUE)
		lexer->state = L_OUT;
	else if (is_assignation(lexer) == TRUE)
		;
	else
	{
		add_to_buffer(lexer);
		lexer->token_type = E_STRING;
	}
}
