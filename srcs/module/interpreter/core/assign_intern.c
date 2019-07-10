/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_intern.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:28:43 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int	update_intern(t_variable *variable, char *data)
{
	if (variable->flag & READONLY_VAR)
	{
		ft_dprintf(STDERR_FILENO, "42sh:`%s': not a valid identifier\n"
				, variable->name);
		return (FAILURE);
	}
	ft_strdel(&variable->data);
	variable->data = expansion_pipeline(g_shell->intern, data);
	if (variable->flag == EXPORT_VAR)
		variable->flag |= SET_VAR;
	return (SUCCESS);
}

static int	insert_intern(t_list **intern, t_list *node)
{
	t_variable	*variable;
	char		*holder;

	variable = node->data;
	if ((holder = expansion_pipeline(*intern, variable->data)) == NULL)
		return (FAILURE);
	ft_strdel(&variable->data);
	variable->data = holder;
	node->next = NULL;
	ft_lstadd(intern, node);
	return (SUCCESS);
}

int			assign_intern(t_registry *shell, t_list **assign)
{
	t_list		*node;
	t_variable	*to_find;

	if (*assign == NULL)
		return (TRUE);
	if (assign_intern(shell, &(*assign)->next) == TRUE)
	{
		to_find = (*assign)->data;
		if (ft_strequ(to_find->name, "PATH"))
			ft_hmap_free_content(&(shell->hash.bin), free);
		if ((node = ft_lstfind(shell->intern, to_find->name, find_var)))
		{
			if (update_intern(node->data, to_find->data) == FAILURE)
				return (FAILURE);
			ft_lstdelone(assign, free_node);
		}
		else
		{
			if (insert_intern(&shell->intern, *assign) == FAILURE)
				return (FAILURE);
		}
		*assign = NULL;
		return (TRUE);
	}
	return (FAILURE);
}
