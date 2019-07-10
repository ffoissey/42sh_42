/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intern_var_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:23:48 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			free_node(void *node)
{
	t_variable	*variable;

	variable = (t_variable *)node;
	if (variable != NULL)
	{
		free(variable->name);
		free(variable->data);
	}
}

static int8_t	del_node(t_list *intern, char *name)
{
	t_list	*tmp;

	tmp = intern;
	intern = intern->next;
	while (intern != NULL)
	{
		if (ft_strequ(((t_variable *)intern->data)->name, name) == TRUE)
		{
			tmp->next = intern->next;
			free_node(intern->data);
			free(intern->data);
			free(intern);
			return (SUCCESS);
		}
		tmp = tmp->next;
		intern = intern->next;
	}
	return (FAILURE);
}

int8_t			free_var(t_list **alst, char *name)
{
	t_list		*intern;
	t_variable	*var;

	intern = *alst;
	if (intern == NULL)
		return (SUCCESS);
	var = (t_variable *)intern->data;
	if (ft_strequ(var->name, name) == TRUE)
	{
		*alst = intern->next;
		free_node(intern->data);
		free(intern->data);
		free(intern);
		return (SUCCESS);
	}
	return (del_node(intern, name));
}
