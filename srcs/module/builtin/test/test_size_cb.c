/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_size_cb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 10:47:10 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/stat.h>

uint8_t		test_e_cb(void *data, void *more, uint8_t type)
{
	char			*pathname;
	struct stat		stat;

	(void)more;
	if (type == BINARY_OP)
	{
		ft_dprintf(2, "42sh: test: -e: binary operator expected\n", type);
		return (ERROR);
	}
	if (!data)
		return (ERROR);
	pathname = data;
	ft_bzero(&stat, sizeof(stat));
	if (lstat(pathname, &stat) == FAILURE)
		return (FALSE);
	return (TRUE);
}

uint8_t		test_s_cb(void *data, void *more, uint8_t type)
{
	char			*pathname;
	struct stat		stat;

	(void)more;
	if (type == BINARY_OP)
	{
		ft_dprintf(2, "42sh: test: -s: binary operator expected\n", type);
		return (ERROR);
	}
	if (!data)
		return (ERROR);
	pathname = data;
	ft_bzero(&stat, sizeof(stat));
	if (lstat(pathname, &stat) == FAILURE)
		return (FALSE);
	if (stat.st_size > 0)
		return (TRUE);
	return (FALSE);
}

uint8_t		test_z_cb(void *data, void *more, uint8_t type)
{
	char			*str;

	(void)more;
	if (type == BINARY_OP)
	{
		ft_dprintf(2, "42sh: test: -z: binary operator expected\n", type);
		return (ERROR);
	}
	if (!data)
		return (ERROR);
	str = data;
	if (ft_strlen(str) == 0)
		return (TRUE);
	return (FALSE);
}
