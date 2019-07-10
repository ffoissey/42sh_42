/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:22:05 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/ioctl.h>

static void			post_process(t_autocomplete *result)
{
	t_list	*lst;
	char	*data;
	char	*new_data;

	lst = result->list;
	while (lst != NULL)
	{
		new_data = NULL;
		data = (char *)lst->data;
		ft_asprintf(&new_data, "%-*s", result->max_len, data);
		ft_strdel(&data);
		lst->data = (void *)new_data;
		lst = lst->next;
	}
}

static size_t		get_elem_by_line(t_autocomplete *result, int col)
{
	size_t	elem_by_line;

	if (col <= 0 || result->max_len <= 0)
		return (1);
	elem_by_line = col / result->max_len;
	if (elem_by_line == 0)
		return (1);
	return (elem_by_line);
}

static size_t		get_elem_by_col(t_autocomplete *result)
{
	size_t			elem_by_col;
	size_t			elem_by_line;
	struct winsize	w;
	int				col;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w) != FAILURE)
		col = w.ws_col;
	else
		col = 0;
	elem_by_line = get_elem_by_line(result, col);
	elem_by_col = result->nb / elem_by_line;
	if (result->nb % elem_by_line)
		elem_by_col++;
	return (elem_by_col);
}

static void			process_print(t_list *lst, size_t elem_by_col)
{
	size_t			i;
	size_t			j;
	t_list			*tmp;

	i = 0;
	ft_putchar_fd('\n', 2);
	while (i < elem_by_col)
	{
		tmp = lst;
		j = i;
		while (j && tmp)
		{
			tmp = tmp->next;
			j--;
		}
		while (tmp != NULL)
		{
			if (j++ % elem_by_col == 0)
				ft_putstr_fd((char *)tmp->data, 2);
			tmp = tmp->next;
		}
		i++;
		if (i != elem_by_col)
			ft_putchar_fd('\n', 2);
	}
}

void				print_possibilities(t_autocomplete *result)
{
	size_t			elem_by_col;

	result->max_len++;
	if (result->list == NULL || result->nb == 0)
		return ;
	post_process(result);
	elem_by_col = get_elem_by_col(result);
	process_print(result->list, elem_by_col);
}
