/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_simple_type_cb.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 10:50:40 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/stat.h>

uint8_t		test_c_cb(void *data, void *more, uint8_t type)
{
	char			*pathname;
	struct stat		stat;

	(void)more;
	if (type == BINARY_OP)
	{
		ft_dprintf(2, "42sh: test: -c: binary operator expected\n", type);
		return (ERROR);
	}
	if (!data)
		return (ERROR);
	pathname = data;
	ft_bzero(&stat, sizeof(stat));
	if (lstat(pathname, &stat) == FAILURE)
		return (FALSE);
	if (S_ISCHR(stat.st_mode) == FALSE)
		return (FALSE);
	return (TRUE);
}

uint8_t		test_f_cb(void *data, void *more, uint8_t type)
{
	char			*pathname;
	struct stat		stat;

	(void)more;
	if (type == BINARY_OP)
	{
		ft_dprintf(2, "42sh: test: -f: binary operator expected\n", type);
		return (ERROR);
	}
	if (!data)
		return (ERROR);
	pathname = data;
	ft_bzero(&stat, sizeof(stat));
	if (lstat(pathname, &stat) == FAILURE)
		return (FALSE);
	if (S_ISREG(stat.st_mode) == FALSE)
		return (FALSE);
	return (TRUE);
}

uint8_t		test_d_cb(void *data, void *more, uint8_t type)
{
	char			*pathname;
	struct stat		stat;

	(void)more;
	if (type == BINARY_OP)
	{
		ft_dprintf(2, "42sh: test: -d: binary operator expected\n", type);
		return (ERROR);
	}
	if (!data)
		return (ERROR);
	pathname = data;
	ft_bzero(&stat, sizeof(stat));
	if (lstat(pathname, &stat) == FAILURE)
		return (FALSE);
	if (S_ISDIR(stat.st_mode) == FALSE)
		return (FALSE);
	return (TRUE);
}
