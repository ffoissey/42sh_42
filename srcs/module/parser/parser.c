/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:41:49 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static uint8_t	manage_error_and_subprompt(t_vector *input,
					enum e_type state, enum e_type type, t_list **lst)
{
	if (need_subprompt(state, type) == TRUE)
		return (parser_subprompt(state, input, lst));
	return (FALSE);
}

static uint8_t	state_is_ok(enum e_type to_find, enum e_type *current,
							enum e_type possible_state[])
{
	uint8_t		i;

	i = 0;
	if (possible_state == NULL)
		return (FALSE);
	if ((g_shell->option.option & INTERACTIVE_OPT) == FALSE
			&& (to_find == E_DLESS
			|| to_find == E_DLESSDASH))
		return (FALSE);
	while (possible_state[i] != E_ERROR)
	{
		if (to_find == possible_state[i])
		{
			*current = to_find;
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

int8_t			parser(t_vector *input, t_list *lst)
{
	t_token			*token;
	t_list			*tmp;
	enum e_type		state;
	static t_graph	*graph = NULL;

	if (graph == NULL)
		graph = init_parser();
	state = E_START;
	tmp = lst;
	while (lst != NULL)
	{
		token = (t_token *)lst->data;
		if ((state_is_ok(token->type, &state, graph[state].good_type)) == FALSE)
		{
			if (manage_error_and_subprompt(input,
						state, token->type, &tmp) == FALSE)
				return (FAILURE);
			lst = tmp;
		}
		else
			tmp = lst;
		lst = lst->next;
	}
	return (SUCCESS);
}
