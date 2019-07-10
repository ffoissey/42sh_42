/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 22:18:22 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		print_action(void *data)
{
	t_action		*action;
	static char		*action_tab[19] = {"A_STDOUT_TRUNCATE_FILE",
										"A_STDOUT_TRUNCATE_FILE_SPECIAL",
										"A_STDOUT_APPEND_FILE",
										"A_STDIN_READ_FILE",
										"A_STDIN_READ_FD",
										"A_IO_TRUNCATE_FILE",
										"A_IO_APPEND_FILE",
										"A_IO_READ_FILE",
										"A_IO_READ_FD",
										"A_DUP",
										"A_CLOSE",
										"A_MOVE",
										"A_HEREDOC",
										"A_HEREDOC_TRIM",
										"A_IO_HEREDOC",
										"A_IO_HEREDOC_TRIM",
										"A_AMBIGOUS_REDIRECT",
										"A_ARGS",
										"A_ASSIGN"};

	action = data;
	ft_dprintf(2, "action type: %s\n", action_tab[action->type]);
	ft_lstiter(action->data, print_token);
}

void		print_command(void *data)
{
	t_command		*command;

	command = data;
	if (command->type & COMMAND_RUN)
	{
		ft_lstiter(command->av, print_token);
		ft_dprintf(2, "--------------------ACTIONS-------------------\n");
		ft_lstiter(command->actions, print_action);
	}
	else if (command->type & COMMAND_ASSIGN)
		ft_lstiter(command->av, print_action);
}

void		print_group(void *data)
{
	t_group		*group;

	group = data;
	ft_dprintf(2, "group type: %d\n", group->type);
	ft_lstiter(group->command_list, print_command);
}

void		analyzer_print_debug(t_registry *shell, t_list *command_group)
{
	if ((shell->option.option & DEBUG_OPT) != FALSE)
	{
		ft_putstr("\n\033[33m------------ ANALYZER --------------\n");
		ft_lstiter(command_group, print_group);
		ft_putendl("------------------------------------\033[0m\n");
	}
}
