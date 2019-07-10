/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:50 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>
#include <limits.h>

static char			*ft_get_curpath(t_list *intern,
							const char *path_give_by_user)
{
	char	*curpath;

	if (path_give_by_user == NULL)
		curpath = ft_strdup(get_home_path(intern));
	else if (ft_strequ(path_give_by_user, "-") == TRUE)
	{
		if ((curpath = get_var(intern, "OLDPWD")) == NULL)
			ft_dprintf(STDERR_FILENO, CD_ERROR_OLDPWD_NOTSET);
		else
			curpath = ft_strdup(curpath);
		return (curpath);
	}
	else if (*path_give_by_user == '/' || *path_give_by_user == '.')
		curpath = ft_strdup(path_give_by_user);
	else
	{
		if ((curpath = is_cdpath_env(intern, path_give_by_user)) == NULL)
			curpath = ft_strdup(path_give_by_user);
	}
	if (curpath == NULL || *curpath == '\0')
	{
		ft_dprintf(STDERR_FILENO, "42sh: cd: no such file or directory\n");
		ft_strdel(&curpath);
	}
	return (curpath);
}

static void			set_oldpwd_and_pwd(t_list *intern, char *curpath,
						char *old_pwd, const t_option option)
{
	char		*pwd;

	(void)intern;
	if (option & P_OPT)
	{
		pwd = NULL;
		pwd = getcwd(NULL, PATH_MAX);
		add_var(&g_shell->intern, "PWD", pwd, SET_VAR | EXPORT_VAR);
		ft_strdel(&pwd);
	}
	else
		add_var(&g_shell->intern, "PWD", curpath, SET_VAR | EXPORT_VAR);
	add_var(&g_shell->intern, "OLDPWD", old_pwd, SET_VAR | EXPORT_VAR);
}

static uint8_t		change_directory(t_list *intern, char *curpath,
						const char *path_give_by_user, const t_option option)
{
	char		*old_pwd;
	uint8_t		ret;

	old_pwd = get_pwd(intern, NO_OPT);
	ret = 1;
	if (check_path(intern, curpath, path_give_by_user) == TRUE)
	{
		ret = SUCCESS;
		set_oldpwd_and_pwd(intern, curpath, old_pwd, option);
		if (ft_strequ(path_give_by_user, "-") == TRUE)
		{
			if (write(1, NULL, 0) == FAILURE)
			{
				ft_putendl_fd("42sh: cd: write error: Bad file descriptor", 2);
				ret = 1;
			}
			else
				ft_printf("%s\n", get_var(g_shell->intern, "PWD"));
		}
	}
	return (exit_cd(intern, &old_pwd, &curpath, ret));
}

static int8_t		is_root(char *path)
{
	uint32_t	i;

	i = 0;
	if (path == NULL || path[0] == '\0')
		return (FALSE);
	while (path[i] != '\0')
	{
		if (path[i] != '/')
			return (FALSE);
		++i;
	}
	path[1] = '\0';
	return (TRUE);
}

uint8_t				cd_blt(t_list *intern, char **av)
{
	char		*curpath;
	t_option	option;

	av++;
	if (((option = set_options(&av, get_option_cd)) == ERROR_OPT)
		|| !one_only_arg(av) || !(curpath = ft_get_curpath(intern, *av)))
		return (2);
	if (is_root(curpath) == FALSE && curpath[ft_strlen(curpath) - 1] == '/')
		curpath[ft_strlen(curpath) - 1] = '\0';
	if ((option & P_OPT) == FALSE)
	{
		if (*curpath != '/')
			if ((curpath = concat_pwd_with_curpath(intern, &curpath)) == NULL)
				return (3);
		if ((curpath = make_curpath_simple(curpath)) == NULL)
		{
			curpath = *av == NULL ? get_var(intern, "HOME") : *av;
			ft_dprintf(STDERR_FILENO, "42sh: cd: %s: %s", ft_strequ(*av, "-") ?
				get_var(intern, "OLDPWD") : curpath, NOFI);
			return (1);
		}
		else if (ft_strlen(curpath) + 1 >= PATH_MAX)
			curpath = get_relative_path(&curpath);
	}
	return (change_directory(intern, curpath, *av, option));
}
