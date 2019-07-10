/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:26:08 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static uint8_t	is_history_end(t_vector *input, const size_t offset)
{
	size_t	len_op;
	int		type;
	char	*current;

	type = START_OPERATOR;
	current = input->buffer + offset;
	if (*current == ' ' || *current == '\t')
		return (TRUE);
	while (type >= 0)
	{
		len_op = ft_strlen(g_shell->grammar[type]);
		if (ft_strnequ(g_shell->grammar[type], current, len_op) == TRUE)
			return (TRUE);
		type--;
	}
	return (FALSE);
}

static int		searching(t_vector *input, t_vector *to_replace, const size_t i,
					uint64_t *option)
{
	int	scale;

	scale = 0;
	if (vct_charat(input, i + scale) == '!')
		scale++;
	if (vct_charat(input, i + scale) == '-')
	{
		*option |= REL;
		scale++;
	}
	while (vct_charat(input, i + scale) != '\0')
	{
		if (is_history_end(input, i + scale) == TRUE)
			break ;
		vct_add(to_replace, vct_charat(input, i + scale));
		scale++;
	}
	if (ft_isnumeric(to_replace->buffer) == TRUE)
		*option |= BY_ID;
	else
		*option |= BY_NAME;
	return (scale);
}

static char		*get_history_return(t_vector *to_replace, const uint64_t option)
{
	char	*search;

	search = history(NULL, to_replace->buffer, option);
	if (search == NULL
			|| ((option & PREV) == FALSE && *to_replace->buffer == '\0'))
	{
		if (option & REL)
			vct_push(to_replace, '-');
		else if (option & PREV)
			vct_push(to_replace, '!');
		vct_push(to_replace, '!');
		ft_dprintf(2, "42sh: %s: event not found\n", to_replace->buffer);
		add_var(&g_shell->intern, "?", "1", READONLY_VAR);
		vct_del(&to_replace);
		return (NULL);
	}
	vct_del(&to_replace);
	return (search);
}

static int		process_history_expansion(t_vector *input, const size_t i)
{
	t_vector	*to_replace;
	uint64_t	option;
	char		*search;
	int			scale;

	option = GET_ENTRY;
	to_replace = vct_new(0);
	scale = 0;
	if (vct_charat(input, i + 1) == '!')
	{
		scale += 2;
		option |= PREV;
	}
	else if (ft_isalnum(vct_charat(input, i + 1)) == TRUE
			|| vct_charat(input, i + 1) == '-')
		scale = searching(input, to_replace, i, &option);
	else
	{
		vct_del(&to_replace);
		return (SUCCESS);
	}
	if ((search = get_history_return(to_replace, option)) == NULL)
		return (FAILURE);
	vct_replace_string(input, i, i + scale, search);
	return (scale);
}

int8_t			history_expansion(t_vector *input)
{
	size_t		i;
	int			ret;
	uint16_t	flag;

	i = 0;
	flag = NO_FLAG;
	while (vct_charat(input, i) != '\0')
	{
		if (flag & BACKSLASH_FLAG)
			flag &= ~BACKSLASH_FLAG;
		if (vct_charat(input, i) == '\\' && flag == NO_FLAG && i++)
			flag |= BACKSLASH_FLAG;
		if (vct_charat(input, i) == '\'' && flag == NO_FLAG)
			flag |= SINGLEQUOTE_FLAG;
		else if (vct_charat(input, i) == '\'' && (flag & SINGLEQUOTE_FLAG))
			flag &= ~SINGLEQUOTE_FLAG;
		else if (vct_charat(input, i) == '!' && flag == NO_FLAG)
		{
			if ((ret = process_history_expansion(input, i)) == FAILURE)
				return (FAILURE);
			i += ret;
		}
		i++;
	}
	return (SUCCESS);
}
