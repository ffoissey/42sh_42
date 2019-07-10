/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cdpath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:35:32 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

static char		*is_valid_path(char *path, const char *to_find)
{
	char	*complete_path;

	if ((complete_path = ft_strjoin(path, to_find)) == NULL)
		return (NULL);
	if (access(complete_path, F_OK) == SUCCESS)
		return (complete_path);
	ft_strdel(&complete_path);
	return (NULL);
}

static uint8_t	add_end_slash(char **path)
{
	size_t	len;
	char	*tmp_path;

	tmp_path = *path;
	len = ft_strlen(tmp_path);
	if (len == 0)
		return (TRUE);
	if (tmp_path[len - 1] != '/')
	{
		tmp_path = *path;
		if ((*path = ft_strjoin(*path, "/")) == NULL)
			return (FALSE);
		ft_strdel(&tmp_path);
	}
	return (TRUE);
}

char			*is_cdpath_env(t_list *intern, const char *to_find)
{
	char		*cd_path;
	char		**tab_cd_path;
	uint32_t	i;

	i = 0;
	if ((cd_path = get_var(intern, "CDPATH")) == NULL)
		return (is_valid_path("./", to_find));
	if ((tab_cd_path = ft_strsplit(cd_path, ":")) == NULL)
		return (NULL);
	while (tab_cd_path[i] != NULL)
	{
		if (add_end_slash(tab_cd_path + i) == FALSE)
		{
			ft_freetab(&tab_cd_path);
			return (NULL);
		}
		if ((cd_path = is_valid_path(tab_cd_path[i], to_find)) != NULL)
		{
			ft_freetab(&tab_cd_path);
			return (cd_path);
		}
		i++;
	}
	ft_freetab(&tab_cd_path);
	return (NULL);
}

uint8_t			check_path(t_list *intern, char *curpath,
						const char *path_give_by_user)
{
	char		*oldpwd;
	struct stat	stat;

	lstat(curpath, &stat);
	if (ft_strequ(path_give_by_user, "-") == TRUE)
	{
		if ((oldpwd = get_var(intern, "OLDPWD")) != NULL)
			path_give_by_user = oldpwd;
	}
	if (access(curpath, F_OK) != SUCCESS)
		ft_dprintf(STDERR_FILENO, "42sh: cd: no such file or directory: %s\n",
				path_give_by_user);
	else if (S_ISDIR(stat.st_mode) == FALSE && S_ISLNK(stat.st_mode) == FALSE)
		ft_dprintf(STDERR_FILENO,
					"42sh: cd: not a directory: %s\n", path_give_by_user);
	else if (access(curpath, R_OK) != SUCCESS)
		ft_dprintf(STDERR_FILENO,
					"42sh: cd: %s: Permission denied\n", path_give_by_user);
	else if (chdir(curpath) == FAILURE)
		ft_dprintf(STDERR_FILENO, "chdir() failed\n");
	else
		return (TRUE);
	return (FALSE);
}
