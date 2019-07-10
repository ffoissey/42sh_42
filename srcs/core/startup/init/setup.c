/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 14:06:27 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int		set_shlvl(t_registry *shell)
{
	char		*shlvl;
	int			nb_shlvl;

	shlvl = get_var(shell->intern, "SHLVL");
	if (shlvl == NULL)
		shlvl = ft_strdup("1");
	else
	{
		nb_shlvl = ft_atoi(shlvl) + 1;
		if (nb_shlvl < 0)
			nb_shlvl = 0;
		else if (nb_shlvl >= 1000)
		{
			ft_dprintf(2, "42sh: warning: shell level"
						" (%d) too high, resetting to 1\n", nb_shlvl);
			nb_shlvl = 1;
		}
		shlvl = ft_itoa(nb_shlvl);
		if (shlvl == NULL)
			return (FAILURE);
	}
	add_var(&shell->intern, "SHLVL", shlvl, EXPORT_VAR | SET_VAR);
	ft_strdel(&shlvl);
	return (SUCCESS);
}

static int8_t	get_env(t_list **alst, char **env)
{
	t_list		*node;
	t_variable	variable;
	size_t		pos;

	while (*env != NULL)
	{
		pos = ft_strcspn(*env, "=");
		variable.name = ft_strsub(*env, 0, pos);
		variable.data = ft_strdup(*env + pos + 1);
		variable.flag = SET_VAR | EXPORT_VAR;
		if (variable.name == NULL || variable.data == NULL)
			return (FAILURE);
		if ((node = ft_lstnew(&variable, sizeof(t_variable))) == NULL)
		{
			free(variable.data);
			free(variable.name);
			return (FAILURE);
		}
		ft_lstaddback(alst, node);
		env++;
	}
	return (TRUE);
}

static void		default_variable(t_list **intern, char *name)
{
	char		*str;
	t_vector	*option;

	str = NULL;
	ft_asprintf(&str, "%d", getpid());
	add_var(intern, "0", name, READONLY_VAR);
	add_var(intern, "$", str, READONLY_VAR);
	add_var(intern, "?", "0", READONLY_VAR);
	add_var(intern, "!", "", READONLY_VAR);
	ft_strdel(&str);
	option = vct_new(0);
	if (g_shell->option.option & COMMAND_OPT)
		vct_add(option, 'c');
	if (g_shell->option.option & DEBUG_OPT)
		vct_add(option, 'd');
	if (g_shell->option.option & HELP_OPT)
		vct_add(option, 'h');
	add_var(intern, "-", vct_get_string(option), READONLY_VAR);
	vct_del(&option);
}

int8_t			set_environment(t_registry *shell, char **av, char **env)
{
	if (*av != NULL)
	{
		if (parse_arg(av, &shell->option) == FAILURE)
		{
			ft_strdel(&(shell->option.command_str));
			return (FAILURE);
		}
	}
	if ((shell->option.option & HELP_OPT) != FALSE)
		return (shell_usage());
	if (get_env(&shell->intern, env) == FAILURE)
	{
		ft_dprintf(2, "[ERROR] - Env malloc failed.\n");
		return (FAILURE);
	}
	default_variable(&shell->intern, av[0]);
	shell->hash.bin = ft_hmap_init(HMAP_BIN_SIZE);
	shell->hash.blt = ft_hmap_init(HMAP_BLT_SIZE);
	generate_grammar();
	if (set_shlvl(shell) == FAILURE)
		return (FAILURE);
	hash_builtin(shell);
	if (shell->hash.blt.used == FALSE)
		ft_dprintf(STDERR_FILENO, "Hashmap blt is empty.\n");
	return (SUCCESS);
}
