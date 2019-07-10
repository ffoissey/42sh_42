/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:26:42 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		print_output(const char *cmd,
					const int fd, const int line, uint64_t const option)
{
	if (option & PRINT_ID)
		ft_dprintf(fd, "%d\t%s\n", line, cmd);
	else if (option & WITHOUT_SPACE)
		ft_dprintf(fd, "%s\n", cmd);
	else
		ft_dprintf(fd, "\t%s\n", cmd);
}

static void		print_reverse(t_history *history, t_param *param,
					const uint64_t option)
{
	t_entry		*entry;
	int			i;

	i = history->nb_of_entries;
	entry = history->entry;
	while (entry != NULL && i >= param->first)
	{
		if (i <= param->last && entry->cmd != NULL)
			print_output(entry->cmd, param->fd, i, option);
		entry = entry->prev;
		i--;
	}
}

static void		print_standard(t_history *history, t_param *param,
					const uint64_t option)
{
	t_entry		*entry;
	int			i;

	i = 1;
	entry = entry_roll_back(history->entry);
	while (entry != NULL && i <= param->last)
	{
		if (i >= param->first && entry->cmd != NULL)
			print_output(entry->cmd, param->fd, i, option);
		entry = entry->next;
		i++;
	}
}

static void		get_elem(t_history *history, const char *elem, t_param *param,
					uint64_t option)
{
	char	*cur;

	param->fd = 1;
	if (elem != NULL && (cur = ft_strstr(elem, "first:")) != NULL)
	{
		param->first = ft_atoi(cur + 6);
		if (param->first <= 0)
			param->first = history->nb_of_entries + param->first + 1;
	}
	else
		param->first = history->nb_of_entries
						- ((option & WITHOUT_SPACE) ? 0 : 15);
	if (elem != NULL && (cur = ft_strstr(elem, "last:")) != NULL)
	{
		param->last = ft_atoi(cur + 5);
		if (param->last <= 0)
			param->last = history->nb_of_entries + param->last + 1;
	}
	else
		param->last = (option & WITHOUT_SPACE) ?
					param->first : history->nb_of_entries;
	if (elem != NULL && (cur = ft_strstr(elem, "fd:")) != NULL)
		param->fd = ft_atoi(cur + 3);
}

void			print_history(t_history *history,
					const char *elem, uint64_t option)
{
	t_param	param;

	ft_bzero(&param, sizeof(t_param));
	get_elem(history, elem, &param, option);
	if (param.last < param.first)
	{
		if (param.first < 0)
			param.first = 0;
		else if (param.first > history->nb_of_entries)
			param.first = history->nb_of_entries;
		if (param.last < 0)
			param.last = 0;
		else if (param.last > history->nb_of_entries)
			param.last = history->nb_of_entries;
		option |= REVERSE;
		int_swap(&param.first, &param.last);
	}
	if (option & REVERSE)
		print_reverse(history, &param, option);
	else
		print_standard(history, &param, option);
}
