/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_interns.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 14:19:01 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void	del_interns(t_sle *sle)
{
	if (sle->interns.ps1 != NULL)
		vct_del(&sle->interns.ps1);
	if (sle->interns.ps2 != NULL)
		vct_del(&sle->interns.ps2);
	if (sle->interns.ps3 != NULL)
		vct_del(&sle->interns.ps3);
	if (sle->interns.pwd != NULL)
		vct_del(&sle->interns.pwd);
	if (sle->interns.username != NULL)
		vct_del(&sle->interns.username);
	if (sle->interns.home != NULL)
		vct_del(&sle->interns.home);
}

void		save_intern_vars(t_registry *shell, t_sle *sle)
{
	char	*data;

	if (shell == NULL)
		return ;
	del_interns(sle);
	data = get_var(shell->intern, INT_PS1);
	sle->interns.ps1 = vct_dups((data != NULL && *data != '\0')
					? data : "prompt> ");
	data = get_var(shell->intern, INT_PS2);
	sle->interns.ps2 = vct_dups((data != NULL && *data != '\0') ? data : "$> ");
	data = get_var(shell->intern, INT_PS3);
	sle->interns.ps3 = vct_dups((data != NULL && *data != '\0') ? data : ">> ");
	data = get_var(shell->intern, "PWD");
	sle->interns.pwd = vct_dups((data != NULL && *data != '\0') ? data : "pwd");
	data = get_var(shell->intern, "USER");
	sle->interns.username = vct_dups((data != NULL && *data != '\0')
				? data : "user");
	data = get_var(shell->intern, "HOME");
	sle->interns.home = vct_dups((data != NULL && *data != '\0') ? data : "~");
}
