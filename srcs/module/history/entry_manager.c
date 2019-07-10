/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 04:22:56 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** delete current entry
*/

void	pop_entry(t_entry **entry, t_entry **head)
{
	t_entry	*next;
	t_entry	*prev;
	t_entry	*cur;

	if (*entry == NULL)
		return ;
	cur = *entry;
	next = cur->next;
	prev = cur->prev;
	if (next != NULL)
		next->prev = prev;
	if (prev != NULL)
		prev->next = next;
	if (cur->next == NULL && cur->prev == NULL)
		*head = NULL;
	else if (cur->next == NULL)
	{
		*head = (*head)->prev;
		(*head)->next = NULL;
	}
	ft_strdel(&cur->cmd);
	free(cur);
}

/*
** free history
*/

void	free_history(t_entry *entry)
{
	if (entry != NULL)
	{
		free_history(entry->prev);
		ft_strdel(&entry->cmd);
		free(entry);
	}
}

/*
** create new entry
*/

t_entry	*create_entry(const char *cmd)
{
	t_entry		*entry;

	if (cmd == NULL)
		return (NULL);
	entry = (t_entry *)malloc(sizeof(t_entry));
	if (entry == NULL)
		return (NULL);
	entry->next = NULL;
	entry->prev = NULL;
	entry->cmd = ft_strdup(cmd);
	return (entry);
}

/*
** add new entry
*/

void	add_entry(t_entry **head, t_entry *new_entry)
{
	if (new_entry == NULL)
		return ;
	if (*head == NULL)
		*head = new_entry;
	else
	{
		(*head)->next = new_entry;
		new_entry->prev = *head;
		*head = new_entry;
	}
}
