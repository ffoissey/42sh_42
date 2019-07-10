/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_permission_cb.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 10:44:02 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/stat.h>

uint8_t		test_u_cb(void *data, void *more, uint8_t type)
{
	char			*pathname;
	struct stat		stat;

	(void)more;
	if (type == BINARY_OP)
	{
		ft_dprintf(2, "42sh: test: -u: binary operator expected\n", type);
		return (ERROR);
	}
	if (!data)
		return (ERROR);
	pathname = data;
	ft_bzero(&stat, sizeof(stat));
	if (lstat(pathname, &stat) == FAILURE)
		return (FALSE);
	if (stat.st_mode & S_ISUID)
		return (TRUE);
	return (FALSE);
}

uint8_t		test_g_cb(void *data, void *more, uint8_t type)
{
	char			*pathname;
	struct stat		stat;

	(void)more;
	if (type == BINARY_OP)
	{
		ft_dprintf(2, "42sh: test: -g: binary operator expected\n", type);
		return (ERROR);
	}
	if (!data)
		return (ERROR);
	pathname = data;
	ft_bzero(&stat, sizeof(stat));
	if (lstat(pathname, &stat) == FAILURE)
		return (FALSE);
	if (stat.st_mode & S_ISGID)
		return (TRUE);
	return (FALSE);
}

uint8_t		test_r_cb(void *data, void *more, uint8_t type)
{
	char			*pathname;
	struct stat		stat;

	(void)more;
	if (type == BINARY_OP)
	{
		ft_dprintf(2, "42sh: test: -r: binary operator expected\n", type);
		return (ERROR);
	}
	if (!data)
		return (ERROR);
	pathname = data;
	ft_bzero(&stat, sizeof(stat));
	if (lstat(pathname, &stat) == FAILURE)
		return (FALSE);
	if (stat.st_mode & S_IRUSR)
		return (TRUE);
	return (FALSE);
}

uint8_t		test_w_cb(void *data, void *more, uint8_t type)
{
	char			*pathname;
	struct stat		stat;

	(void)more;
	if (type == BINARY_OP)
	{
		ft_dprintf(2, "42sh: test: -w: binary operator expected\n", type);
		return (ERROR);
	}
	if (!data)
		return (ERROR);
	pathname = data;
	ft_bzero(&stat, sizeof(stat));
	if (lstat(pathname, &stat) == FAILURE)
		return (FALSE);
	if (stat.st_mode & S_IWUSR)
		return (TRUE);
	return (FALSE);
}

uint8_t		test_x_cb(void *data, void *more, uint8_t type)
{
	char			*pathname;
	struct stat		stat;

	(void)more;
	if (type == BINARY_OP)
	{
		ft_dprintf(2, "42sh: test: -x: binary operator expected\n", type);
		return (ERROR);
	}
	if (!data)
		return (ERROR);
	pathname = data;
	ft_bzero(&stat, sizeof(stat));
	if (lstat(pathname, &stat) == FAILURE)
		return (FALSE);
	if (stat.st_mode & S_IXUSR)
		return (TRUE);
	return (FALSE);
}
