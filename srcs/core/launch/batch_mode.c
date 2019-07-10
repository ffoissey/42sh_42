/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   batch_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:16:26 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

static void				read_input(t_registry *shell)
{
	t_vector	*cmd;
	char		*line;

	line = NULL;
	cmd = NULL;
	while (get_next_line(STDIN_FILENO, &line) > 0)
	{
		if (ft_strcheck(line, ft_isprint) == TRUE)
		{
			cmd = vct_dups(line);
			if (verif_line(cmd) == TRUE)
				execution_pipeline(shell, &cmd);
			vct_del(&cmd);
		}
		else if (line != NULL)
			ft_putendl_fd("42sh: Not a valid input", 2);
		ft_strdel(&line);
	}
}

void					batch_mode(t_registry *shell)
{
	t_vector	*cmd;

	if (shell->option.option & COMMAND_OPT)
	{
		if (shell->option.command_str != NULL
				&& ft_strcheck(shell->option.command_str, ft_isprint) == TRUE)
		{
			cmd = vct_dups(shell->option.command_str);
			if (verif_line(cmd) == TRUE)
				execution_pipeline(shell, &cmd);
		}
		else
			ft_putendl_fd("42sh: Not a valid input", 2);
	}
	else
		read_input(shell);
}
