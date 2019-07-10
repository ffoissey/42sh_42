/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:57 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

uint8_t				echo_blt(t_list *intern, char **av)
{
	t_option	option;
	int8_t		ret;

	++av;
	(void)intern;
	option = 0;
	ret = SUCCESS;
	while (ft_strequ("-n", *av) == TRUE)
	{
		option |= N_OPT;
		++av;
	}
	while (*av != NULL)
	{
		ret = ft_putstr(*av);
		++av;
		if (*av != NULL)
			ret = ft_putstr(" ");
	}
	if ((option & N_OPT) == FALSE)
		ret = ft_putstr("\n");
	if (ret == FAILURE)
		ft_putendl_fd("42sh: echo: write error: Bad file descriptor", 2);
	return (ret == FAILURE ? 1 : SUCCESS);
}
