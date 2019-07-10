/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:23:09 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

uint8_t				set_blt(t_list *intern, char **av)
{
	av++;
	if (*av == NULL)
	{
		if (write(1, NULL, 0) == FAILURE)
		{
			ft_putendl_fd("42sh: set: write error: Bad file descriptor", 2);
			return (1);
		}
		print_lst(intern, STDOUT_FILENO, "", SET_VAR);
	}
	return (SUCCESS);
}
