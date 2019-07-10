/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:50 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

uint8_t				unset_blt(t_list *intern, char **av)
{
	uint8_t ret;

	(void)intern;
	++av;
	ret = SUCCESS;
	while (*av != NULL)
	{
		if (is_valid_variable(*av) == FALSE)
		{
			ft_dprintf(STDERR_FILENO,
					"42sh: unset: `%s': not a valid identifier\n", *av);
			ret = 2;
		}
		else if (g_shell->intern != NULL)
			free_var(&g_shell->intern, *av);
		if (ft_strequ(*av, "PATH") == TRUE)
			ft_hmap_free_content(&(g_shell->hash.bin), free);
		av++;
	}
	return (ret);
}
