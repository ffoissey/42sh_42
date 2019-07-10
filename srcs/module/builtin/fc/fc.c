/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:28:31 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_option		get_option_fc(char *s, t_option option)
{
	if (ft_isnumeric(s) == TRUE)
		return (option | STOP_OPT);
	while (*s)
	{
		if (*s == 'n')
			option |= N_OPT;
		else if (*s == 'l')
			option |= L_OPT;
		else if (*s == 'r')
			option |= R_OPT;
		else if (*s == 's')
		{
			option |= S_OPT;
		}
		else if (*s == 'e' && (option == NO_OPT))
			return (option | E_OPT | STOP_OPT);
		else
		{
			ft_dprintf(STDERR_FILENO, "42sh: fc: -%c%s", *s, FC_INV);
			ft_dprintf(STDERR_FILENO, "%s%s or %s", FC1, FC2, FC3);
			return (ERROR_OPT);
		}
		s++;
	}
	return (option);
}

static char		*get_fc_options(char ***av, t_option *option)
{
	char	*editor;

	editor = NULL;
	if (*av == NULL || (*option = set_options(av, get_option_fc)) == ERROR_OPT)
		return (NULL);
	if (*option & E_OPT)
	{
		if (ft_strequ(**av, "-e") == TRUE && *(*av + 1) == NULL)
		{
			ft_dprintf(STDERR_FILENO, "%s\n%s%s or %s", FC_E, FC1, FC2, FC3);
			*option = ERROR_OPT;
			return (NULL);
		}
		if (ft_strequ(**av, "-e") == TRUE)
		{
			(*av)++;
			editor = ft_strdup(**av);
		}
		else
			editor = ft_strdup(**av + 2);
		(*av)++;
	}
	return (editor);
}

static char		*get_default_editor(t_list *intern)
{
	char	*editor;

	editor = get_var(intern, "FCEDIT");
	editor = ft_strdup(editor == NULL ? "ed" : editor);
	return (editor);
}

uint8_t			fc_blt(t_list *intern, char **av)
{
	t_option	option;
	char		*editor;
	int			ret;

	++av;
	option = 0;
	ret = 0;
	if ((g_shell->option.option & RECORD_HISTORY_OPT) == FALSE)
		return (SUCCESS);
	editor = get_fc_options(&av, &option);
	if (option == ERROR_OPT)
		ret = 2;
	else if (option & S_OPT)
		ret = fc_redo(av);
	else if (option & L_OPT)
		ret = fc_list(av, option);
	else
	{
		if (editor == NULL)
			editor = get_default_editor(intern);
		ret = fc_editor(av, editor);
	}
	history(g_shell, NULL, RESET_HEAD);
	ft_strdel(&editor);
	return (ret);
}
