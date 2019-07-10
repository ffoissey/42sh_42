/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:50 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_option			get_option_export(char *s, t_option option)
{
	while (*s)
	{
		if (*s == 'p')
			option |= P_OPT;
		else
		{
			ft_dprintf(STDERR_FILENO,
					"42sh: export: -%c: invalid option\n", *s);
			ft_putendl_fd(EXPORT_USAGE, STDERR_FILENO);
			return (ERROR_OPT);
		}
		s++;
	}
	return (option);
}

static void			export_var(t_list *intern, t_variable *variable)
{
	if (variable->data)
	{
		add_var(&g_shell->intern, variable->name, variable->data,
				EXPORT_VAR | SET_VAR);
		if (ft_strequ(variable->name, "PATH") == TRUE)
			ft_hmap_free_content(&(g_shell->hash.bin), free);
	}
	else
	{
		if ((variable->data = get_var(intern, variable->name)) == NULL)
			add_var(&g_shell->intern, variable->name, "", EXPORT_VAR);
		else
		{
			variable->data = ft_strdup(variable->data);
			add_var(&g_shell->intern, variable->name, variable->data,
					SET_VAR | EXPORT_VAR);
		}
	}
}

static void			get_name_and_data(t_variable *variable, char *arg)
{
	char		*equal;

	variable->name = ft_strdup(arg);
	variable->data = NULL;
	if ((equal = ft_strchr(arg, '=')) != NULL)
	{
		equal = ft_strchr(variable->name, '=');
		*equal = '\0';
		variable->data = ft_strdup(ft_strchr(arg, '=') + 1);
	}
}

static uint8_t		export_process(t_list *intern, char **av)
{
	t_variable	*variable;
	uint8_t		ret;

	ret = SUCCESS;
	while (*av != NULL)
	{
		variable = (t_variable *)malloc(sizeof(t_variable));
		if (variable == NULL)
			return (FAILURE);
		ft_bzero(variable, sizeof(t_variable));
		get_name_and_data(variable, *av);
		if (is_valid_variable(variable->name) == FALSE)
		{
			ft_dprintf(STDERR_FILENO,
					"42sh: export: `%s': not a valid identifier\n", *av);
			ret = 2;
		}
		else
			export_var(intern, variable);
		free_node((void *)variable);
		free(variable);
		av++;
	}
	return (ret);
}

uint8_t				export_blt(t_list *intern, char **av)
{
	t_option	option;

	av++;
	option = 0;
	if (((option |= set_options(&av, get_option_export)) == ERROR_OPT))
		return (2);
	if (*av == NULL)
	{
		if (write(1, NULL, 0) == FAILURE)
		{
			ft_putendl_fd("42sh: export: write error: Bad file descriptor", 2);
			return (1);
		}
		print_lst(intern, STDOUT_FILENO,
					(option & P_OPT) ? "export " : "", EXPORT_VAR);
	}
	return (export_process(intern, av));
}
