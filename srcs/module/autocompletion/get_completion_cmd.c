/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_completion_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 17:21:15 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

static uint8_t	is_exclusive(t_list *result, char *data)
{
	while (result != NULL)
	{
		if (ft_strequ((char *)result->data, data) == TRUE)
			return (FALSE);
		result = result->next;
	}
	return (TRUE);
}

static void		find_bin(char *input, DIR *dir, t_autocomplete *result,
					char *dirname)
{
	struct dirent		*mydir;
	char				*data;
	size_t				len;

	len = input == NULL ? 0 : ft_strlen(input);
	while ((mydir = readdir(dir)) != NULL)
	{
		if (len == 0 || ft_strnequ(mydir->d_name, input, len) == TRUE)
		{
			if (ft_strequ(mydir->d_name, ".")
				|| ft_strequ(mydir->d_name, "..")
				|| is_a_directory(dirname, mydir->d_name) == TRUE)
				continue ;
			data = ft_strjoin(mydir->d_name, " ");
			if (is_exclusive(result->list, data) == TRUE)
			{
				ft_lstadd(&result->list, ft_lstnew(data, ft_strlen(data) + 1));
				result->max_len = get_maxlen(result->max_len, ft_strlen(data));
				result->nb++;
			}
			ft_strdel(&data);
		}
	}
}

void			find_builtin(char *input, t_autocomplete *result)
{
	char				*data;
	size_t				len;
	int					i;
	static const char	*blt[] = {"echo", "cd", "hash", "exit", "test"
									"type", "export", "set", "unset",
									"pwd", "fc", "bg", "fg", "jobs", NULL};

	len = input == NULL ? 0 : ft_strlen(input);
	i = 0;
	while ((blt[i]) != NULL)
	{
		if (len == 0 || ft_strnequ(blt[i], input, len) == TRUE)
		{
			data = ft_strjoin(blt[i], " ");
			ft_lstadd(&result->list, ft_lstnew(data, ft_strlen(data) + 1));
			result->max_len = get_maxlen(result->max_len, ft_strlen(data));
			result->nb++;
			ft_strdel(&data);
		}
		i++;
	}
}

void			get_completion_cmd(char *input, t_autocomplete *result,
							t_registry *shell)
{
	uint32_t	i;
	char		**tab;
	DIR			*dir;

	result->nb = 0;
	find_builtin(input, result);
	if (get_var(shell->intern, "PATH") == NULL)
		return ;
	tab = ft_strsplit(get_var(shell->intern, "PATH"), ":");
	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i] != NULL)
	{
		if ((dir = opendir(tab[i])) != NULL)
		{
			find_bin(input, dir, result, tab[i]);
			closedir(dir);
		}
		i++;
	}
	ft_freetab(&tab);
}
