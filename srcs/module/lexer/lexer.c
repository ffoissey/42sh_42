/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:23:19 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_list			*lexer(t_vector *input, uint8_t opt)
{
	t_lexer	lexer;

	init_lexer(&lexer, input);
	if (opt == SHELL)
	{
		while (lexer.state != L_FINISH)
			lexer.state == L_OUT ? out_lexer(&lexer) : process_lexer(&lexer);
		lexer_print_debug(g_shell, lexer.tokens);
	}
	else if (opt == MATHS)
	{
		while (lexer.state != L_FINISH)
			lexer.state == L_OUT ? out_lexer_m(&lexer)
				: process_maths_lexer(&lexer);
		lexer_m_print_debug(g_shell, lexer.tokens);
	}
	vct_del(&lexer.buffer);
	return (lexer.tokens);
}
