/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 20:06:45 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		valid_heredoc_setup(t_redirect *redirect, int from, int to)
{
	redirect->type |= FD_REDIRECT;
	redirect->from = from;
	redirect->to = to;
	return (SUCCESS);
}

int		check_delimiter(char **delimiter, t_vector **vector, int fd)
{
	if (!(*vector) || ft_strequ((*vector)->buffer, *delimiter) == TRUE)
	{
		close(fd);
		ft_strdel(delimiter);
		vct_del(vector);
		return (SUCCESS);
	}
	return (FAILURE);
}

void	update_input(char *string)
{
	t_vector	*vector;
	char		*input;

	if ((input = get_var(g_shell->intern, "_input")))
	{
		vector = vct_dups(input);
		vct_scat(vector, string, ft_strlen(input));
		vct_scat(vector, "\n", 1);
		add_var(&g_shell->intern, "_input",
					vct_get_string(vector), READONLY_VAR);
		vct_del(&vector);
	}
}

int		write_heredoc(t_vector **vector, int fd, int trim)
{
	char		*string;
	int			index;

	index = 0;
	string = expansion_pipeline(g_shell->intern, (*vector)->buffer);
	if (string)
	{
		while (trim == TRIM_ON && ft_strchr(" \t", string[index]))
			index++;
		update_input(string + index);
		ft_putendl_fd(string + index, fd);
		ft_strdel(&string);
		vct_del(vector);
	}
	return (0);
}
