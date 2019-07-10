/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 21:03:03 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			is_export(void *data, void *to_find)
{
	t_variable *variable;

	(void)to_find;
	variable = data;
	if (variable->flag & EXPORT_VAR && variable->flag & SET_VAR)
		return (TRUE);
	return (FALSE);
}

int			copy_var(void *src, void *dest)
{
	t_variable *source;
	t_variable *destination;

	source = src;
	destination = dest;
	destination->name = ft_strdup(source->name);
	destination->data = ft_strdup(source->data);
	return (0);
}

int			variable_update(void *context, void *data)
{
	t_list		*tmp_env;
	t_variable	*variable;
	char		*holder;

	tmp_env = context;
	variable = data;
	if ((holder = expansion_pipeline(g_shell->intern, variable->data)) == NULL)
		return (-1);
	if (ft_strequ(variable->name, "PATH") == TRUE)
		ft_hmap_free_content(&(g_shell->hash.bin), free);
	ft_strdel(&variable->data);
	variable->data = holder;
	add_var(&tmp_env, variable->name, variable->data, variable->flag);
	return (0);
}

static char	*variable_to_tab(void *data)
{
	t_variable	*variable;
	char		*str;

	variable = data;
	str = NULL;
	ft_asprintf(&str, "%s=%s", variable->name, variable->data);
	return (str);
}

char		**generate_env(t_registry *shell, t_list *local_env)
{
	char	**env;
	t_list	*tmp_env;

	tmp_env = ft_lstfilter(shell->intern, NULL, is_export, copy_var);
	if (ft_lstiter_ctx(local_env, tmp_env, variable_update) == -1)
		return (NULL);
	env = ft_lsttotab(tmp_env, variable_to_tab);
	ft_lstdel(&tmp_env, free_node);
	return (env);
}
