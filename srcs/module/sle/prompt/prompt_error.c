/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:49:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

inline t_vector		*read_error(t_registry *shell, t_sle *sle)
{
	if (ft_strequ(sle->prompt.state, INT_PS1) == FALSE)
	{
		g_shell->sigint = FALSE;
		sle->prompt.state = INT_PS1;
		return (NULL);
	}
	if (g_shell->sigint == TRUE)
	{
		g_shell->sigint = FALSE;
		return (prompt(shell, sle));
	}
	return (NULL);
}
