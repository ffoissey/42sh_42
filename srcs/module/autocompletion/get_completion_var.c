/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_completion_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:20:59 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		add_var_to_list(t_autocomplete *result,
						char *var_name)
{
	char	*data;

	data = NULL;
	if (result->type == VARIABLE_BRACKET_TYPE)
		ft_asprintf(&data, "{$%s} ", var_name);
	else
		ft_asprintf(&data, "$%s ", var_name);
	ft_lstadd(&result->list, ft_lstnew(data, ft_strlen(data) + 1));
	result->max_len = get_maxlen(result->max_len, ft_strlen(data));
	ft_strdel(&data);
	result->nb++;
}

void			get_completion_var(char *input,
					t_autocomplete *result, t_registry *shell)
{
	t_list		*env;
	t_variable	*var;
	size_t		len;

	result->nb = 0;
	len = input == NULL ? 0 : ft_strlen(input);
	env = shell->intern;
	while (env != NULL)
	{
		var = env->data;
		if ((len == 0 || ft_strnequ(var->name, input, len) == TRUE)
				&& (var->flag & SET_VAR))
			add_var_to_list(result, var->name);
		env = env->next;
	}
}
