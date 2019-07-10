/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 07:18:22 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

void				valid_command(t_vector **input, t_list **command_group)
{
	add_var(&g_shell->intern, "_input", vct_get_string(*input), READONLY_VAR);
	vct_del(input);
	interpreter(g_shell, command_group);
	load_signal_profile(DFLT_PROFILE);
}

int					invalid_input(t_vector **input, t_list **tokens)
{
	if (g_shell->option.option & RECORD_HISTORY_OPT)
		history(g_shell, vct_get_string(*input), ADD_ENTRY);
	add_var(&g_shell->intern, "?", "1", READONLY_VAR);
	ft_lstdel(tokens, del_token);
	vct_del(input);
	return (FAILURE);
}

int8_t				execution_pipeline(t_registry *shell, t_vector **input)
{
	t_list			*command_group;
	t_list			*tokens;

	command_group = NULL;
	tokens = lexer(*input, SHELL);
	lexer_print_debug(shell, tokens);
	if (parser(*input, tokens) == FAILURE)
		return (invalid_input(input, &tokens));
	command_group = analyzer(&tokens);
	if (command_group == NULL)
		return (invalid_input(input, &tokens));
	else
		valid_command(input, &command_group);
	vct_del(input);
	return (SUCCESS);
}
