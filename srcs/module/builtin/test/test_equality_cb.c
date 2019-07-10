/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_equality_cb.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 08:49:09 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

uint8_t		test_equal_cb(void *data, void *more, uint8_t type)
{
	char	*s1;
	char	*s2;

	s1 = data;
	s2 = more;
	if (type == UNARY_OP)
	{
		ft_dprintf(2, "42sh: test: =: unary operator expected\n", type);
		return (ERROR);
	}
	if (!s1 || !s2)
		return (ERROR);
	return (ft_strequ(s1, s2));
}

uint8_t		test_diff_cb(void *data, void *more, uint8_t type)
{
	char	*s1;
	char	*s2;

	s1 = data;
	s2 = more;
	if (type == UNARY_OP)
	{
		ft_dprintf(2, "42sh: test: !=: unary operator expected\n", type);
		return (ERROR);
	}
	if (!s1 || !s2)
		return (ERROR);
	if (ft_strequ(s1, s2) == TRUE)
		return (FALSE);
	return (TRUE);
}

uint8_t		test_eq_cb(void *data, void *more, uint8_t type)
{
	char	*n1;
	char	*n2;

	n1 = data;
	n2 = more;
	if (type == UNARY_OP)
	{
		ft_dprintf(2, "42sh: test: -eq: unary operator expected\n", type);
		return (ERROR);
	}
	if (ft_isnumeric(n1) == FALSE || ft_isnumeric(n2) == FALSE)
	{
		ft_dprintf(2, "42sh: test: -eq: integer expression expected\n", type);
		return (ERROR);
	}
	if (!n1 || !n2)
		return (ERROR);
	if (ft_atoi(n1) == ft_atoi(n2))
		return (TRUE);
	return (FALSE);
}

uint8_t		test_ne_cb(void *data, void *more, uint8_t type)
{
	char	*n1;
	char	*n2;

	n1 = data;
	n2 = more;
	if (type == UNARY_OP)
	{
		ft_dprintf(2, "42sh: test: -ne: unary operator expected\n", type);
		return (ERROR);
	}
	if (ft_isnumeric(n1) == FALSE || ft_isnumeric(n2) == FALSE)
	{
		ft_dprintf(2, "42sh: test: -ne: integer expression expected\n", type);
		return (ERROR);
	}
	if (!n1 || !n2)
		return (ERROR);
	if (ft_atoi(n1) != ft_atoi(n2))
		return (TRUE);
	return (FALSE);
}
