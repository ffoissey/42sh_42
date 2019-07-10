/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_subroutine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 14:58:14 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static uint8_t	extend_subroutine(t_vector *line, size_t *i, uint8_t type)
{
	if (is_end_backslash(line, *i) == TRUE)
		backslash_process(line);
	else if (is_brace_exp(line, *i) == TRUE)
		return (brace_exp_routine(line, i));
	else if (is_maths_exp(line, *i) == TRUE)
		return (maths_exp_routine(line, i));
	else if (vct_charat(line, *i) == '\'')
		return (single_quote_routine(line, i));
	else if (vct_charat(line, *i) == '\"')
		return (double_quote_routine(line, i));
	else if (type == PAR_TYPE && vct_charat(line, *i) == '(')
		return (parenthesis(line, i));
	return (TRUE);
}

uint8_t			parenthesis(t_vector *line, size_t *i)
{
	(*i)++;
	while (vct_charat(line, *i) != ')')
	{
		if (vct_charat(line, *i) == '\0')
		{
			if (subprompt_call(line, PRINT_MATHS) == FALSE)
				return (FALSE);
			continue ;
		}
		else if (vct_charat(line, *i) == '\\')
			(*i)++;
		else if (extend_subroutine(line, i, PAR_TYPE) == FALSE)
			return (FALSE);
		(*i)++;
	}
	return (TRUE);
}

uint8_t			maths_exp_routine(t_vector *line, size_t *i)
{
	uint8_t	par;

	(*i) += 2;
	par = 0;
	while (par != 2)
	{
		if (parenthesis(line, i) == FALSE)
			return (FALSE);
		par++;
	}
	return (TRUE);
}

uint8_t			brace_exp_routine(t_vector *line, size_t *i)
{
	(*i) += 2;
	while (vct_charat(line, *i) != '}')
	{
		if (vct_charat(line, *i) == '\0')
		{
			if (subprompt_call(line, PRINT_BRACE) == FALSE)
				return (FALSE);
			continue ;
		}
		else if (vct_charat(line, *i) == '\\')
			(*i)++;
		else if (extend_subroutine(line, i, DEFAULT_TYPE) == FALSE)
			return (FALSE);
		(*i)++;
	}
	return (TRUE);
}

uint8_t			verif_line(t_vector *line)
{
	size_t		i;

	i = 0;
	while (vct_charat(line, i) != '\0')
	{
		if (is_end_backslash(line, i) == TRUE)
		{
			backslash_process(line);
			if (subprompt_call(line, PRINT_NL) == FALSE)
				return (FALSE);
			continue ;
		}
		else if (vct_charat(line, i) == '\\')
			i++;
		else if (extend_subroutine(line, &i, DEFAULT_TYPE) == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}
