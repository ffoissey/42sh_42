/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 11:59:35 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 17:03:14 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

uint8_t			verif_arg(char *s)
{
	static char	*long_s = "-9223372036854775808";
	size_t		len;
	size_t		i;
	uint8_t		ok;

	ok = FALSE;
	i = s[0] == '-' ? 1 : 0;
	long_s += i == 1 ? 0 : 1;
	len = ft_strlen(s + i);
	while (s[i] != '\0' && long_s[i] != '\0' && ok != 2)
	{
		if (s[i] < '0' || s[i] > '9' || len > 19
				|| (len == 19 && ok == FALSE && long_s[i] < s[i]))
			ok = 2;
		else if (s[i] < long_s[i])
			ok = TRUE;
		i++;
	}
	if (ok == 2 || (s[0] == '-' && s[1] == '\0') || (i == 19 && s[18] >= '8'))
	{
		ft_dprintf(2, "42sh: exit: %s: numeric argument required\n", s);
		return (2);
	}
	return ((uint8_t)ft_atoi(s));
}

static uint8_t	job_notified(void)
{
	if (g_shell->job_list != NULL && g_shell->job_notified == 0)
	{
		g_shell->job_notified++;
		ft_dprintf(2, "There are stopped jobs.\n");
		return (FALSE);
	}
	else
		return (TRUE);
}

uint8_t			exit_blt(t_list *intern, char **av)
{
	uint8_t			ret;

	(void)intern;
	if (job_notified() == FALSE)
		return (1);
	ret = g_shell == NULL ? SUCCESS : ft_atoi(get_var(g_shell->intern, "?"));
	if (av == NULL)
		shell_exit_routine(g_shell, SUCCESS);
	++av;
	if (av != NULL && *av != NULL)
	{
		if (*(av + 1) != NULL)
		{
			ft_putendl_fd("42sh: exit: too many arguments", STDERR_FILENO);
			return (2);
		}
		ret = verif_arg(*av);
	}
	shell_exit_routine(g_shell, ret);
	return (SUCCESS);
}
