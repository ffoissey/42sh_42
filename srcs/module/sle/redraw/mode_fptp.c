/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_fptp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 15:51:27 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	redrawmode_fpte(t_sle *sle)
{
	sle->window.point2 = (sle->rd_info.line_len
					> sle->rd_info.disp_len)
					? sle->rd_info.line_len
					: sle->rd_info.disp_len;
	++sle->window.point2;
	redrawmode_fptp(sle);
}

void	redrawmode_fstp(t_sle *sle)
{
	sle->window.point1 = 0;
	redrawmode_fptp(sle);
}
