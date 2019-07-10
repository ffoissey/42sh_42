/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_tools2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:23:24 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			check_nl(t_registry *shell, t_sle *sl, t_vector *line)
{
	uint32_t	index;
	t_vector	*concat;
	t_vector	*hardcopy;

	(void)sl;
	index = 0;
	while (vct_charat(line, index) != '\0')
	{
		if (vct_charat(line, index) == '\\'
				&& vct_charat(line, index + 1) == '\n')
		{
			vct_pop(line);
			vct_pop(line);
			hardcopy = vct_dup(line);
			sle(shell, &concat, SLE_PS3_PROMPT);
			vct_ncat(hardcopy, concat, vct_len(concat));
			vct_replace_string(line, 0, vct_len(hardcopy),
							vct_get_string(hardcopy));
			vct_del(&hardcopy);
			vct_del(&concat);
		}
		++index;
	}
}

void			prompt_mode(t_prompt *prompt, char *state,
					char *missing)
{
	prompt->state = state;
	prompt->missing_char = missing;
}
