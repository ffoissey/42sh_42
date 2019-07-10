/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intern_var_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 14:06:50 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			print_lst(t_list *lst, int fd, char *prefix, t_option flag)
{
	t_variable	*variable;

	while (lst != NULL)
	{
		variable = (t_variable *)lst->data;
		if (variable->flag & flag)
		{
			if ((flag & EXPORT_VAR) && (variable->flag & SET_VAR) == FALSE)
				ft_dprintf(fd, "%s%s\n", prefix,
							variable->name, variable->data);
			else if (*variable->data != '\0')
				ft_dprintf(fd, "%s%s=%s\n", prefix,
							variable->name, variable->data);
			else
				ft_dprintf(fd, "%s%s=\n", prefix, variable->name);
		}
		lst = lst->next;
	}
}

int8_t			create_node(t_list **alst, char *name, char *data,
					t_option flag)
{
	t_variable	variable;
	t_list		*newdir;

	if (name == NULL)
		return (FAILURE);
	ft_bzero(&variable, sizeof(t_variable));
	variable.name = ft_strdup(name);
	variable.data = ft_strdup(data);
	variable.flag = flag;
	if (variable.name == NULL || variable.data == NULL)
		return (FAILURE);
	if ((newdir = ft_lstnew(&variable, sizeof(t_variable))) == NULL)
		return (FAILURE);
	ft_lstaddback(alst, newdir);
	return (SUCCESS);
}

int8_t			change_node(t_list **alst, char *name, char *data,
					t_option flag)
{
	t_list *ptr;

	ptr = *alst;
	if (name == NULL || data == NULL)
		return (FAILURE);
	while (ptr != NULL)
	{
		if (ft_strequ(((t_variable *)ptr->data)->name, name) == TRUE)
		{
			ft_strdel(&(((t_variable *)ptr->data)->data));
			((t_variable *)ptr->data)->data = ft_strdup(data);
			((t_variable *)ptr->data)->flag = flag;
			return (SUCCESS);
		}
		ptr = ptr->next;
	}
	return (create_node(alst, name, data, flag));
}

size_t			list_export_size(t_list *lst)
{
	size_t		count;
	t_variable	*variable;

	count = 0;
	while (lst != NULL)
	{
		variable = (t_variable *)lst->data;
		if (variable->flag & EXPORT_VAR)
			count++;
		lst = lst->next;
	}
	return (count);
}
