/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 20:06:27 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int8_t	shell_option_letter(t_opt *option, char *arg)
{
	if (*arg != '-')
	{
		ft_dprintf(2, "42sh: %c: invalid option\n", *arg);
		return (FAILURE);
	}
	++arg;
	if (*arg == '-')
		return (FAILURE);
	while (*arg != '\0')
	{
		if (*arg == 'h')
			option->option |= HELP_OPT;
		else if (*arg == 'd')
			option->option |= DEBUG_OPT;
		else if (*arg == 'c')
			option->option |= COMMAND_OPT;
		else
		{
			ft_dprintf(2, "42sh: -%c: invalid option\n", *arg);
			return (FAILURE);
		}
		++arg;
	}
	return (SUCCESS);
}

static int8_t	shell_option_word(t_opt *option, const char *arg)
{
	if (ft_strequ(arg, "--help") == TRUE)
		option->option |= HELP_OPT;
	else if (ft_strequ(arg, "--debug") == TRUE)
		option->option |= DEBUG_OPT;
	else
	{
		if (ft_strnequ(arg, "--", 2) == TRUE)
			ft_dprintf(2, "42sh: %s: invalid option\n", arg);
		return (FAILURE);
	}
	return (SUCCESS);
}

int8_t			parse_arg(char **av, t_opt *option)
{
	while (*av != NULL)
	{
		if (**av != '-' || ft_strequ(*av, "--") == TRUE)
			break ;
		else if (shell_option_word(option, *av) == FAILURE)
			if (shell_option_letter(option, *av) == FAILURE)
				return (shell_usage());
		av++;
	}
	if (option->option & COMMAND_OPT)
	{
		if (*av == NULL)
		{
			ft_dprintf(2, "42sh: need command after -c option\n", av);
			return (shell_usage());
		}
		option->command_str = ft_strdup(*av);
	}
	return (SUCCESS);
}
