/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 13:50:12 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		is_all(void *data, void *to_find)
{
	(void)data;
	(void)to_find;
	return (TRUE);
}

int		launch_builtin(char **av, t_list **l_env, t_builtin builtin)
{
	int		status;

	status = 0;
	if (ft_strequ(av[0], "exit") == TRUE)
	{
		ft_lstdel(l_env, free_node);
		status = builtin(NULL, av);
	}
	else
		status = builtin(*l_env, av);
	ft_lstdel(l_env, free_node);
	return (status);
}
