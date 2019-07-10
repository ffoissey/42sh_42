/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_subroutine_tools.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:37:10 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

uint8_t			subprompt_call(t_vector *line, uint32_t option)
{
	t_vector			*new_input;
	static const char	*prompt_type[] = {PROMPT_PIPE, PROMPT_QUOTE,
						PROMPT_DQUOTE, PROMPT_BQUOTE, PROMPT_NL, PROMPT_AND,
						PROMPT_OR, PROMPT_BRACE, PROMPT_MATHS};

	if ((g_shell->option.option & INTERACTIVE_OPT) == FALSE)
	{
		ft_dprintf(2, "42sh: %s %s\n", UNEXPECTED_EOF, prompt_type[option]);
		add_var(&g_shell->intern, "?", "1", READONLY_VAR);
		return (FALSE);
	}
	history(g_shell, vct_get_string(line), ADD_ENTRY);
	new_input = NULL;
	sle(g_shell, &new_input, option | SLE_PS2_PROMPT);
	if (new_input == NULL || (option != PRINT_QUOTE && option != PRINT_DQUOTE
				&& do_history_exp(&new_input) == FAILURE))
	{
		vct_del(&new_input);
		history(g_shell, NULL, POP_ENTRY);
		return (FALSE);
	}
	history(g_shell, NULL, POP_ENTRY);
	vct_ncat(line, new_input, vct_len(new_input));
	vct_del(&new_input);
	return (TRUE);
}

uint8_t			is_end_backslash(t_vector *line, int index)
{
	if (vct_charat(line, index) == '\\'
		&& vct_charat(line, index + 1) == '\n'
		&& vct_charat(line, index + 2) == '\0')
		return (TRUE);
	return (FALSE);
}

uint8_t			is_brace_exp(t_vector *line, int index)
{
	if (vct_charat(line, index) == '$'
		&& vct_charat(line, index + 1) == '{')
		return (TRUE);
	return (FALSE);
}

uint8_t			is_maths_exp(t_vector *line, int index)
{
	if (vct_charat(line, index) == '$'
		&& vct_charat(line, index + 1) == '('
		&& vct_charat(line, index + 2) == '(')
		return (TRUE);
	return (FALSE);
}

void			backslash_process(t_vector *line)
{
	vct_pop(line);
	vct_pop(line);
}
