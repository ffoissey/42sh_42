/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 13:51:48 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>
#include <sys/stat.h>

static uint8_t	ft_exists_and_is_exec(char *path)
{
	struct stat		tmp;

	if (access(path, F_OK) == FAILURE)
		return (FALSE);
	if (stat(path, &tmp) == SUCCESS)
	{
		if (S_ISREG(tmp.st_mode) && access(path, X_OK) == SUCCESS)
			return (TRUE);
	}
	return (FALSE);
}

static int8_t	find_bin(char *path, char *bin, char **buf)
{
	ft_asprintf(buf, "%s/%s", path, bin);
	if (*buf == NULL)
	{
		ft_putendl_fd("42sh: hash: [CRITICAL] Malloc error\n", 2);
		return (FAILURE);
	}
	if (ft_exists_and_is_exec(*buf) == TRUE)
		return (SUCCESS);
	ft_strdel(buf);
	return (NOT_FOUND);
}

static int8_t	check_binary(t_list *intern)
{
	if (get_var(intern, "PATH") == NULL)
		return (FAILURE);
	if (ft_strequ("", get_var(intern, "PATH")))
		return (FAILURE);
	return (SUCCESS);
}

int8_t			find_in_path(t_list *intern, char *bin, char **buf)
{
	uint32_t	i;
	int8_t		ret;
	char		**tab;

	ret = NOT_FOUND;
	if (is_path_to_bin(bin) == TRUE)
		return (NOT_FOUND);
	if (check_binary(intern) == FAILURE)
		return (NOT_FOUND);
	tab = ft_strsplit(get_var(intern, "PATH"), ":");
	if (tab == NULL)
	{
		ft_putendl_fd("42sh: hash: [CRITICAL] Malloc error\n", 2);
		return (FAILURE);
	}
	i = 0;
	while (tab[i] != NULL)
	{
		ret = find_bin(tab[i], bin, buf);
		if (ret != NOT_FOUND)
			break ;
		i++;
	}
	ft_freetab(&tab);
	return (ret);
}
