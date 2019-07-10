/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 20:28:28 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	init_lexer(t_lexer *lexer, t_vector *input)
{
	ft_bzero(lexer, sizeof(t_lexer));
	lexer->buffer = vct_new(0);
	lexer->input = input;
	lexer->index = 0;
	lexer->state = L_PROCESS;
	lexer->token_type = E_DEFAULT;
	lexer->last_token_type = E_DEFAULT;
	lexer->last_token_mtype = E_M_DEFAULT;
	lexer->token_mtype = E_M_DEFAULT;
	lexer->assignation = POSSIBLE;
}

char	get_input(t_lexer *lexer, uint8_t pos)
{
	if (pos & NEXT_CHAR)
		return (vct_charat(lexer->input, lexer->index + 1));
	else if (pos & NEXT_NEXT_CHAR)
		return (vct_charat(lexer->input, lexer->index + 2));
	return (vct_charat(lexer->input, lexer->index));
}

void	add_to_buffer(t_lexer *lexer)
{
	vct_add(lexer->buffer, lexer->input->buffer[lexer->index]);
	lexer->index++;
}

uint8_t	last_is_redirect(t_lexer *lexer)
{
	if (lexer->last_token_type == E_DLESS
		|| lexer->last_token_type == E_DGREAT
		|| lexer->last_token_type == E_LESS
		|| lexer->last_token_type == E_GREAT
		|| lexer->last_token_type == E_LESSAND
		|| lexer->last_token_type == E_GREATAND
		|| lexer->last_token_type == E_ANDGREAT
		|| lexer->last_token_type == E_ANDDGREAT
		|| lexer->last_token_type == E_DLESSDASH)
		return (TRUE);
	return (FALSE);
}
