/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_simple.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:50 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

static void		ft_process_transform(const char *path, char **new_path)
{
	char	*curpath;
	char	*tmp_path;

	if (ft_strequ(path, "..") == TRUE)
	{
		if ((ft_strequ(*new_path, "/") == FALSE)
			&& (tmp_path = ft_strrchr((*new_path) + 1, '/')) != NULL)
			*tmp_path = '\0';
		else
			*(*new_path + 1) = '\0';
	}
	else
	{
		if ((ft_strequ(*new_path, "/")) == FALSE)
			curpath = ft_strjoin("/", path);
		else
			curpath = ft_strdup(path);
		tmp_path = *new_path;
		*new_path = ft_strjoin(tmp_path, curpath);
		ft_strdel(&curpath);
		ft_strdel(&tmp_path);
	}
}

static char		*transform_elem_path(const char *path, char **new_path)
{
	if (path != NULL && ft_strequ(path, ".") == FALSE)
	{
		ft_process_transform(path, new_path);
		if (access(*new_path, F_OK) != SUCCESS)
		{
			ft_strdel(new_path);
			return (NULL);
		}
	}
	return (*new_path);
}

char			*make_curpath_simple(char *curpath)
{
	char			*new_path;
	char			**tab_path;
	uint32_t		i;

	i = 0;
	if (ft_strequ(curpath, "/"))
		return (curpath);
	if ((tab_path = ft_strsplit(curpath, "/")) == NULL)
	{
		ft_strdel(&curpath);
		return (NULL);
	}
	new_path = ft_strdup("/");
	ft_strdel(&curpath);
	while (tab_path[i] != NULL)
	{
		if ((new_path = transform_elem_path(tab_path[i++], &new_path)) == NULL)
		{
			ft_freetab(&tab_path);
			return (NULL);
		}
	}
	ft_freetab(&tab_path);
	return (new_path);
}

uint8_t			one_only_arg(char **arg)
{
	if (*arg == NULL)
		return (TRUE);
	if (*(arg + 1) != NULL)
	{
		ft_dprintf(STDERR_FILENO, "42sh: cd: Too many arguments\n");
		return (FALSE);
	}
	return (TRUE);
}
