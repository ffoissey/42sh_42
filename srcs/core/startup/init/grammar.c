/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:42:01 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void	generate_maths_grammar(void)
{
	static const char	*grammar[NB_OF_MTOKENS] = {M_TIMES, M_DIVIDE, M_MODULO,
								M_PLUS, M_MINUS, M_OPENP, M_CLOSEP,
								M_LESS, M_LESSEQ,
								M_GREAT, M_GREATEQ, M_EQUAL, M_NEQUAL,
								M_AND, M_OR, M_DPLUS, M_DMINUS,
								M_ASSIGN, M_STRING,
								M_NB_DEC, M_NB_OCT, M_NB_HEX,
								M_END, M_START};

	g_shell->grammar_m = grammar;
}

static void	generate_shell_grammar(void)
{
	static const char	*grammar[NB_OF_TOKENS] = {N_PIPE, N_GREAT, N_LESS,
							N_SEMICOLON, N_AND, N_NEWLINE, N_DAND, N_OR,
							N_DLESS, N_DGREAT, N_LESSAND,
							N_GREATAND, N_ANDDGREAT, N_ANDGREAT,
							N_DLESSDASH, N_IO_NUMBER, N_ASSIGN,
							N_STRING, N_END, N_ERROR, N_START};

	g_shell->grammar = grammar;
}

void		generate_grammar(void)
{
	generate_shell_grammar();
	generate_maths_grammar();
}
