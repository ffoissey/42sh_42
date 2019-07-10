/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 12:53:56 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

uint8_t			test_not(uint8_t status)
{
	if (status == TRUE)
		return (FALSE);
	return (TRUE);
}

int8_t			test_single_arg(char *arg)
{
	if (!arg || ft_strequ(arg, ""))
		return (FALSE);
	return (TRUE);
}

int8_t			two_arg_input(t_hash *callbacks, char **av)
{
	char		*type;
	char		*arg;
	t_test_cb	test;

	type = av[0];
	arg = av[1];
	if ((test = ft_hmap_getdata(callbacks, type)) == NULL)
	{
		ft_dprintf(2, "42sh: test: %s: unary operator expected\n", type);
		return (ERROR);
	}
	return (test(arg, NULL, UNARY_OP));
}

int8_t			three_arg_input(t_hash *callbacks, char **av)
{
	char		*type;
	char		*first;
	char		*second;
	t_test_cb	test;

	type = av[1];
	first = av[0];
	second = av[2];
	if ((test = ft_hmap_getdata(callbacks, type)) == NULL)
	{
		ft_dprintf(2, "42sh: test: %s: binary operator expected\n", type);
		return (ERROR);
	}
	return (test(first, second, BINARY_OP));
}
