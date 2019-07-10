/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_maths_interface.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:59:11 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static t_token	generate_token_m(t_lexer *lexer)
{
	t_token	token;

	token.type = lexer->token_mtype;
	token.data = NULL;
	if (token.type == E_M_STRING
		|| token.type == E_M_NB_DEC
		|| token.type == E_M_NB_OCT
		|| token.type == E_M_NB_HEX)
		token.data = ft_strdup(vct_get_string(lexer->buffer));
	return (token);
}

void			out_lexer_m(t_lexer *lexer)
{
	t_token	token;
	t_list	*node;

	token = generate_token_m(lexer);
	if ((node = ft_lstnew(&token, sizeof(token))) == NULL)
	{
		ft_strdel(&token.data);
		return ;
	}
	ft_lstaddback(&lexer->tokens, node);
	lexer->state = lexer->token_mtype == E_M_END ? L_FINISH : L_PROCESS;
	lexer->last_token_mtype = lexer->token_mtype;
	lexer->token_mtype = E_M_DEFAULT;
	vct_reset(lexer->buffer);
}

void			process_maths_lexer(t_lexer *lexer)
{
	if (is_input_end_m(lexer) == TRUE)
		lexer->state = L_OUT;
	else if (is_delimiter_m(lexer) == TRUE)
		lexer->index++;
	else if (is_operator_m(lexer) == TRUE)
		lexer->state = L_OUT;
	else if (is_number_m(lexer) == TRUE)
		add_to_buffer(lexer);
	else
	{
		add_to_buffer(lexer);
		lexer->token_mtype = E_M_STRING;
	}
}
