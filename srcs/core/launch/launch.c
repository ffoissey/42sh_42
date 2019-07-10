/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:16:26 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

inline uint8_t	is_shell_interactive(t_registry *shell)
{
	if ((shell->option.option & COMMAND_OPT) == FALSE
			&& isatty(STDIN_FILENO) != 0)
	{
		shell->option.option |= INTERACTIVE_OPT;
		return (TRUE);
	}
	return (FALSE);
}

void			launch_shell(t_registry *shell)
{
	char		*last_command;
	int			status;

	if (isatty(STDOUT_FILENO) != 1)
	{
		ft_dprintf(2, "42sh: stdout: bad file descriptor\n");
		return ;
	}
	if (is_shell_interactive(shell) == TRUE)
		interactive_mode(shell);
	else
		batch_mode(shell);
	last_command = get_var(g_shell->intern, "?");
	status = ft_atoi(last_command);
	term_mode(TERMMODE_DFLT);
	shell_exit_routine(g_shell, status);
}
