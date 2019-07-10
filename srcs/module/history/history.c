/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 04:23:08 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void	add_new_entry(t_history *history, char *new)
{
	size_t		len;
	char		*dup;

	if (new == NULL || *new == '\0')
		return ;
	dup = ft_strdup(new);
	len = ft_strlen(new);
	if (len > 0 && dup[len - 1] == '\n')
		dup[len - 1] = '\0';
	if (*dup == '\0')
	{
		ft_strdel(&dup);
		return ;
	}
	add_entry(&history->entry, create_entry(dup));
	history->head_ptr = history->entry;
	history->nb_of_entries++;
	ft_strdel(&dup);
}

static void	delete_entry(t_history *history, const int id)
{
	t_entry		*entry;
	int			rel_id;

	rel_id = (id <= 0 || id > history->nb_of_entries)
				? 0 : history->nb_of_entries - id;
	entry = history->entry;
	while (entry != NULL)
	{
		if (rel_id == 0)
		{
			pop_entry(&entry, &history->entry);
			history->head_ptr = history->entry;
			history->nb_of_entries--;
			return ;
		}
		entry = entry->prev;
		rel_id--;
	}
}

static void	init_and_reset(t_registry *shell,
					t_history *history, const uint64_t option)
{
	if (option & INIT_HISTORY)
	{
		ft_bzero(history, sizeof(t_history));
		history->first_search = TRUE;
		read_histfile(shell, history);
	}
	else if (option & RESET_HEAD)
	{
		history->first_search = TRUE;
		history->head_ptr = history->entry;
	}
}

char		*history(t_registry *shell, const char *name, const uint64_t option)
{
	static t_history	history;

	if ((option & INIT_HISTORY) || (option & RESET_HEAD))
		init_and_reset(shell, &history, option);
	else if (option & ADD_ENTRY)
		add_new_entry(&history, (char *)name);
	else if (option & POP_ENTRY)
	{
		delete_entry(&history, (name == NULL || *name == '\0')
							? -1 : ft_atoi(name));
	}
	else if (option & GET_ENTRY)
		return (get_entry(&history, name, option));
	else if (option & PRINT_HISTORY)
		print_history(&history, name, option);
	else if (option & WRITE_HISTFILE)
		write_histfile(shell, &history);
	else if (option & FREE_HISTORY)
		free_history(history.entry);
	return (NULL);
}
