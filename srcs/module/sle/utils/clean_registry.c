/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_registry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:14:21 by nrechati          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void	sle_destroy(t_sle *sle)
{
	ft_strdel(&sle->termcaps.clear_line);
	ft_strdel(&sle->termcaps.clear_screen);
	ft_strdel(&sle->termcaps.standout_off);
	ft_strdel(&sle->termcaps.standout_on);
	ft_strdel(&sle->termcaps.clear);
	ft_strdel(&sle->termcaps.down);
	ft_strdel(&sle->termcaps.right);
	ft_strdel(&sle->termcaps.left);
	ft_strdel(&sle->termcaps.up);
	ft_strdel(&sle->termcaps.hidden_cursor);
	ft_strdel(&sle->termcaps.normal_cursor);
	vct_del(&sle->window.displayed_line);
	vct_del(&sle->interns.ps1);
	vct_del(&sle->interns.ps2);
	vct_del(&sle->interns.ps3);
	vct_del(&sle->interns.pwd);
	vct_del(&sle->interns.username);
	vct_del(&sle->interns.home);
	vct_del(&sle->line);
	vct_del(&sle->sub_line);
	vct_del(&sle->heredocln);
	vct_del(&sle->line_save);
	vct_del(&sle->search_hit);
	vct_del(&sle->clip);
}

void		sle_teardown(t_sle *sle)
{
	sle_destroy(sle);
}
