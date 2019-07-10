/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_profile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 18:20:57 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void	load_profile(struct sigaction signal_profile[NB_SIGNALS])
{
	int		i;

	i = 1;
	while (i < NB_SIGNALS)
	{
		sigaction(i, &signal_profile[i], NULL);
		++i;
	}
}

void		load_signal_profile(uint8_t profile_flag)
{
	static struct sigaction tab_signal_dflt[NB_SIGNALS];
	static struct sigaction tab_signal_sle[NB_SIGNALS];
	static struct sigaction tab_signal_exec[NB_SIGNALS];

	if (profile_flag == INIT_HANDLER)
	{
		init_tab_signal_dflt(tab_signal_dflt);
		init_tab_signal_sle(tab_signal_sle);
		init_tab_signal_exec(tab_signal_exec);
	}
	else if (profile_flag == DFLT_PROFILE)
		load_profile(tab_signal_dflt);
	else if (profile_flag == SLE_PROFILE)
		load_profile(tab_signal_sle);
	else if (profile_flag == EXEC_PROFILE)
		load_profile(tab_signal_exec);
}
