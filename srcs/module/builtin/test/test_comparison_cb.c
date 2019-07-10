/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_comparison_cb.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 08:48:25 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

uint8_t		test_gt_cb(void *data, void *more, uint8_t type)
{
	char	*n1;
	char	*n2;

	n1 = data;
	n2 = more;
	if (type == UNARY_OP)
	{
		ft_dprintf(2, "42sh: test: -gt: unary operator expected\n", type);
		return (ERROR);
	}
	if (ft_isnumeric(n1) == FALSE || ft_isnumeric(n2) == FALSE)
	{
		ft_dprintf(2, "42sh: test: -gt: integer expression expected\n", type);
		return (ERROR);
	}
	if (!n1 || !n2)
		return (ERROR);
	if (ft_atoi(n1) > ft_atoi(n2))
		return (TRUE);
	return (FALSE);
}

uint8_t		test_ge_cb(void *data, void *more, uint8_t type)
{
	char	*n1;
	char	*n2;

	n1 = data;
	n2 = more;
	if (!n1 || !n2)
		return (ERROR);
	if (type == UNARY_OP)
	{
		ft_dprintf(2, "42sh: test: -ge: unary operator expected\n", type);
		return (ERROR);
	}
	if (ft_isnumeric(n1) == FALSE || ft_isnumeric(n2) == FALSE)
	{
		ft_dprintf(2, "42sh: test: -ge: integer expression expected\n", type);
		return (ERROR);
	}
	if (ft_atoi(n1) >= ft_atoi(n2))
		return (TRUE);
	return (FALSE);
}

uint8_t		test_lt_cb(void *data, void *more, uint8_t type)
{
	char	*n1;
	char	*n2;

	n1 = data;
	n2 = more;
	if (!n1 || !n2)
		return (ERROR);
	if (type == UNARY_OP)
	{
		ft_dprintf(2, "42sh: test: -lt: unary operator expected\n", type);
		return (ERROR);
	}
	if (ft_isnumeric(n1) == FALSE || ft_isnumeric(n2) == FALSE)
	{
		ft_dprintf(2, "42sh: test: -lt: integer expression expected\n", type);
		return (ERROR);
	}
	if (ft_atoi(n1) < ft_atoi(n2))
		return (TRUE);
	return (FALSE);
}

uint8_t		test_le_cb(void *data, void *more, uint8_t type)
{
	char	*n1;
	char	*n2;

	n1 = data;
	n2 = more;
	if (!n1 || !n2)
		return (ERROR);
	if (type == UNARY_OP)
	{
		ft_dprintf(2, "42sh: test: -le: unary operator expected\n", type);
		return (ERROR);
	}
	if (ft_isnumeric(n1) == FALSE || ft_isnumeric(n2) == FALSE)
	{
		ft_dprintf(2, "42sh: test: -le: integer expression expected\n", type);
		return (ERROR);
	}
	if (ft_atoi(n1) <= ft_atoi(n2))
		return (TRUE);
	return (FALSE);
}
