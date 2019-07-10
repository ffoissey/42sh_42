/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:30:08 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t			get_first_last(char **av, char **param)
{
	char	*last;
	char	*tmp;

	last = NULL;
	while (*av != NULL)
	{
		if (ft_isnumeric(*av) == FALSE)
			return (FAILURE);
		if (*param == NULL)
			*param = ft_strjoin("first:", *av);
		else
		{
			last = ft_strjoin("last:", *av);
			tmp = *param;
			*param = ft_strjoin(tmp, last);
			ft_strdel(&tmp);
			ft_strdel(&last);
			return (SUCCESS);
		}
		av++;
	}
	return (SUCCESS);
}

uint8_t			fc_list(char **av, t_option option)
{
	char		*param;
	uint64_t	opt_history;

	param = NULL;
	opt_history = PRINT_HISTORY;
	if ((option & N_OPT) == FALSE)
		opt_history |= PRINT_ID;
	if ((option & R_OPT))
		opt_history |= REVERSE;
	if (get_first_last(av, &param) == FAILURE)
	{
		ft_dprintf(STDERR_FILENO,
				"42sh: fc: history specification out of range\n");
		ft_strdel(&param);
		return (1);
	}
	if (write(1, NULL, 0) == FAILURE)
	{
		ft_putendl_fd("42sh: fc: write error: Bad file descriptor", 2);
		ft_strdel(&param);
		return (1);
	}
	history(NULL, param, opt_history);
	ft_strdel(&param);
	return (SUCCESS);
}
